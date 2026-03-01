#include "FileButton.h"

#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>
#include <imgui/imgui.h>
#include "../Image.h"
#include "../common.h"
#include "hge/filesystem/filesystem.h"
#include "ui/window.h"
#include "ui/windows/script_editor.h"
#include "ui/windows/content_browser.h"
#include "ui/windows/texture_editor.h"

enum ExtensionAction {
	None,
	SwitchFolder,
	OpenScriptEditor,
	OpenTextureEditor,
	OpenSoundEditor,
	OpenMediaEditor
};
struct ExtensionEntry
{
	const char* extension;
	const char* image;
	ExtensionAction action;
};
static ExtensionEntry extensions[] = {
	{ ".png", "img-file128", OpenTextureEditor },
	{ ".jpg", "img-file128", OpenTextureEditor },
	{ ".jpeg", "img-file128",OpenTextureEditor },

	{ ".hs", "hs-file128", OpenScriptEditor},
	{ ".mat", "mat-file128", OpenScriptEditor},

	{ ".mp3", "sound-file128", OpenSoundEditor},
	{ ".wav", "sound-file128", OpenSoundEditor},

	{ ".mp4", "media-file128", OpenMediaEditor},
};

void Action(ExtensionAction _action, const char* _fileParameter, const char* _fileName, editor::ContentBrowser* _parent)
{
	switch (_action)
	{
		case None: { break; }
		case SwitchFolder:
		{
			_parent->history_.Push(_fileParameter);
			_parent->dir_ = _fileParameter;
			break;
		}
		case OpenScriptEditor:
		{
			auto* win = static_cast<editor::ScriptEditor*>(editor::GetWindow("ScriptEditor"));
			win->visible = true;

			std::ifstream file(_fileParameter, std::ios::binary);
			if (!file)
			{
				throw std::runtime_error("File reading error");
			}
			std::ostringstream ss;
			ss << file.rdbuf(); // lit tout le contenu
			win->SetContent(ss.str().c_str());
			win->editing_path = _fileParameter;
			break;
		}
		case OpenTextureEditor:
		{
			auto* win = static_cast<editor::TextureEditor*>(editor::GetWindow("TextureEditor"));
			size_t textureSize;
			std::string textureFile = HGE_filesystem::HGE_GetFileContent(_fileParameter, &textureSize, true);
			HRL_id texture = HRL_CreateTexture(textureFile.c_str(), textureSize);
			win->SetTexture(texture);
			win->visible = true;
		}
	}
}

static ImVec2 itemSize(128.f, 128.f);
static std::string selectedFile;

void Element(const char* _filename, const char* _image, ExtensionAction _action, const char* _path, editor::ContentBrowser* _parent)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::InvisibleButton(_filename, itemSize);

	//draw de l'image par dessus le bouton
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddImage(editor::GetImage(_image)->GetBackendID(), pos, ImVec2(pos.x + itemSize.x, pos.y + itemSize.y), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
	if (selectedFile == _path)
	{
		drawList->AddRect(pos, ImVec2(pos.x + itemSize.x, pos.y + itemSize.y), IM_COL32(10,10,100,180), 16.f);
	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		selectedFile = _path;
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		Action(_action, _path, _filename, _parent);
	}
}

namespace editor
{
	void FileButton(const fs::directory_entry& _entry, ContentBrowser* _parent)
	{
		std::string extension = _entry.path().extension().string();
		std::string filename = _entry.path().filename().string();
		std::string path = _entry.path().string();

		ImGui::TableNextColumn();

		if (_entry.is_directory())
		{
			Element(filename.c_str(), "folder128", SwitchFolder, path.c_str(), _parent);

			//nom du dossier en bas
			ImGui::Text(filename.c_str());
		}
		else
		{
			bool matched = false;
			for (const auto& e : extensions)
			{
				std::string loopExt = e.extension;
				if (extension == loopExt)
				{
					Element(filename.c_str(), e.image, e.action, path.c_str(), _parent);

					//on affiche pas l'extension si l'extension est connue par le moteur
					fs::path fileNamePath = filename;
					//file sans l'extension
					fs::path withoutExt = fileNamePath.stem();
					std::string fileNameWithoutExt = withoutExt.string();
					ImGui::Text(fileNameWithoutExt.c_str());

					matched = true;
					break;
				}
			}
			if (!matched)
			{
				Element(filename.c_str(), "generic-file128", None, path.c_str(), _parent);
				ImGui::Text(filename.c_str());
			}
		}
	}
}
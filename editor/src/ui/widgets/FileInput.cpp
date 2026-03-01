#include "FileInput.h"

#include <imgui/imgui.h>
#include <tinyfiledialogs/tinyfiledialogs.h>

#include "ui/common.h"
#include <string>
#include <filesystem>
#include <iostream>

static bool CheckExtension(const char* filepath, const char* const* filters, int filterCount)
{
	if (!filepath) return false;

	std::filesystem::path p(filepath);
	std::string ext = p.extension().string(); // récupère ".txt"

	// Parcours tous les filtres
	for (int i = 0; i < filterCount; ++i)
	{
		const char* filter = filters[i]; // ex: "*.txt"

		// Ignore "*." et compare avec l'extension
		if (filter[0] == '*' && filter[1] == '.')
		{
			std::string filterExt = &filter[1]; // ".txt"
			if (ext == filterExt)
				return true;
		}
	}

	return false; // aucun filtre correspondant
}

namespace editor
{
	std::string FileInput(char* _buffer, size_t _bufferSize, const char* _label, const char *_defaultDir, int _filterNum, char const * const * const _filters, char const * const _fileDescription, const char* _emptyDesctiprion)
	{
		ImGui::PushFont(getFont("std"));

		//largeur du bouton "..."
		float buttonWidth = 30.f;

		ImGui::Text(_label);
		ImGui::SameLine();

		std::string t = "##" + std::string(_label);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - buttonWidth - 10.f);
		ImGui::InputText(t.c_str(), _buffer, _bufferSize);
		ImGui::SameLine();

		if(ImGui::Button("...", ImVec2(buttonWidth, 0)))
		{
			const char* result = tinyfd_openFileDialog(
				"Choose File",
				_defaultDir,
				_filterNum,
				_filters,
				_fileDescription,
				0
				);

			if (result)
			{
				strncpy(_buffer, result, _bufferSize - 1); //copie sécurisée
				_buffer[_bufferSize-1] = '\0'; //s'assure de la terminaison
			}
		}


		if (_buffer[0] != '\0')
		{
			if (std::filesystem::exists(_buffer))
			{
				if (!CheckExtension(_buffer, _filters, _filterNum))
				{
					ImGui::TextColored(ImVec4(0.9f, 0.1f, 0.1f, 1.f),"File does not respect extension");
				}
			}
			else
			{
				ImGui::TextColored(ImVec4(0.9f, 0.1f, 0.1f, 1.f),"File does not exist");
			}
		}
		else
		{
			ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.f), _emptyDesctiprion);
		}

		ImGui::PopFont();

		return std::string{_buffer};
	}

	std::string DirectoryInput(char* _buffer, size_t _bufferSize, const char* _label, const char *_defaultDir)
	{
		float buttonWidth = 30.f;

		ImGui::PushFont(getFont("std"));

		ImGui::Text(_label);
		ImGui::SameLine();

		std::string t = "##" + std::string(_label);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - buttonWidth - 10.f);
		ImGui::InputText(t.c_str(), _buffer, _bufferSize);
		ImGui::SameLine();

		if(ImGui::Button("...", ImVec2(buttonWidth, 0)))
		{
			const char* result = tinyfd_selectFolderDialog(
					"Choose Folder",
					_defaultDir
			);

			if (result)
			{
				strncpy(_buffer, result, _bufferSize - 1);
				_buffer[_bufferSize-1] = '\0';
			}
		}

		ImGui::PopFont();
		return std::string{_buffer};
	}
}
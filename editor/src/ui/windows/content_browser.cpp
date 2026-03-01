#include "content_browser.h"

#include "../common.h"
#include "../widgets/FileButton.h"

#include <imgui/imgui.h>

#include <iostream>
#include <fstream>

#include <string>

#ifdef _WIN32
#include <windows.h>
void OpenInExplorer(const std::string& path)
{
	// Convertit en wchar_t si nécessaire
	std::wstring wpath(path.begin(), path.end());

	// ShellExecuteW ouvre le dossier
	ShellExecuteW(
			nullptr,
			L"open",           // action "ouvrir"
			wpath.c_str(),     // dossier à ouvrir
			nullptr,
			nullptr,
			SW_SHOWDEFAULT
	);
}
#endif


typedef enum {
	None,
	File,
	Folder
}file_type_e;

namespace editor
{
	ContentBrowser::ContentBrowser()
	{
		title = "Content Browser";

		dir_ = "";
	}

	void ContentBrowser::content()
	{
		if (dir_.empty())
		{
			return;
		}

		//menu clic droit
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Open in Explorer"))
			{
				OpenInExplorer(dir_.string());
			}
			if (ImGui::BeginMenu("New"))
			{
				char nameBuff[256] = "";
				file_type_e typeBuffer = None;
				std::string extension;
				if (ImGui::BeginMenu("Horizon Script File"))
				{
					if (ImGui::InputText("##hsfile", nameBuff, 256, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						extension = ".hs";
						typeBuffer = File;
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Material File"))
				{
					if (ImGui::InputText("##matfile", nameBuff, 256, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						extension = ".mat";
						typeBuffer = File;
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Generic File"))
				{
					if (ImGui::InputText("##genericfile", nameBuff, 256, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						extension = "";
						typeBuffer = File;
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Folder"))
				{
					if (ImGui::InputText("##folder", nameBuff, 256, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						extension = "";
						typeBuffer = Folder;
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
				//menu new
				if (typeBuffer == File)
				{
					//creer un fichier vide
					std::string fileStr = nameBuff + extension;
					fs::path p = dir_ / fileStr;
					std::ofstream ofs(p);
					if (!ofs)
					{
						std::cerr << "Error while creating file\n";
					}
					ofs.close();
				}
				else if (typeBuffer == Folder)
				{
					//créer un folder
					fs::path p = dir_ / nameBuff;
					fs::create_directory(p);
				}
			}
			ImGui::EndPopup();
		}

		if (ImGui::IsMouseClicked(3) && history_.CanBack())
		{
			// bouton latéral arrière
			std::cout << "arriere" << std::endl;
			dir_ = history_.Back();
		}

		if (ImGui::IsMouseClicked(4) && history_.CanForward())
		{
			// bouton latéral avant
			std::cout << "avant" << std::endl;
			dir_ = history_.Forward();
		}

		ImGui::PushFont(getFont("std"));

		std::string dirStr = dir_.string();
		ImGui::Text(dirStr.c_str());

		float itemSize = 128.0f;
		float spacing = ImGui::GetStyle().ItemSpacing.x;
		float width = ImGui::GetContentRegionAvail().x;

		int columns = (int)(width / (itemSize + spacing));
		if (columns < 1) columns = 1;

		if (ImGui::BeginTable("Grid", columns))
		{
			for (const fs::directory_entry& entry : fs::directory_iterator(dir_))
			{
				FileButton(entry, this);
			}
			ImGui::EndTable();
		}

		ImGui::PopFont();
	}
}

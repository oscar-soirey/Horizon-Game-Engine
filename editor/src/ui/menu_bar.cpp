#include "menu_bar.h"

#include <imgui/imgui.h>

#include "common.h"
#include "window.h"


namespace editor
{
	void ShowMenuBar()
	{
		const std::unordered_map<std::string, std::unique_ptr<Window>> & _wins = GetWindows();
		ImGui::PushFont(getFont("std"));
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open Project", nullptr, GetWindow("OpenProject")->visible))
				{
					INVERT_BOOL(GetWindow("OpenProject")->visible);
				}

				if (ImGui::MenuItem("Project Configuration", nullptr, GetWindow("ProjectConfiguration")->visible))
				{
					INVERT_BOOL(GetWindow("ProjectConfiguration")->visible);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo")) { /* action */ }
				if (ImGui::MenuItem("Redo")) { /* action */ }

				if (ImGui::MenuItem("Preferences"))
				{

				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Content Browser", nullptr, GetWindow("ContentBrowser")->visible))
				{
					INVERT_BOOL(GetWindow("ContentBrowser")->visible);
				}

				if (ImGui::MenuItem("Script Editor", nullptr, GetWindow("ScriptEditor")->visible))
				{
					INVERT_BOOL(GetWindow("ScriptEditor")->visible);
				}

				if (ImGui::MenuItem("Texture Editor", nullptr, GetWindow("TextureEditor")->visible))
				{
					INVERT_BOOL(GetWindow("TextureEditor")->visible);
				}

				if (ImGui::MenuItem("Viewport", nullptr, GetWindow("Viewport")->visible))
				{
					INVERT_BOOL(GetWindow("Viewport")->visible);
				}

				if (ImGui::MenuItem("Place Actors", nullptr, GetWindow("PlaceActors")->visible))
				{
					INVERT_BOOL(GetWindow("PlaceActors")->visible);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
			ImGui::PopFont();
		}
	}
}
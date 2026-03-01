#include "project_configuration.h"


#include "../common.h"

#include <imgui/imgui.h>

#include "../widgets/TitleIcon.h"
#include "../widgets/FileInput.h"
#include "../widgets/ComboBox.h"
#include "ui/Image.h"

const char* backends[6] = {
	"Auto (Recommended)",
	"OpenGL 3.3",
	"OpenGL 4.5",
	"Vulkan",
	"DirectX 11",
	"DirectX 12"
};


namespace editor
{
	ProjectConfiguration::ProjectConfiguration()
	{
		title = "Project Configuration";
	}

	void ProjectConfiguration::content()
	{
		static int selected = 0;

		TitleIcon("Project Configuration", GetImage("gear64"));

		ImGui::PushFont(getFont("std"));

		ImGui::BeginChild("left", ImVec2(220, 0), 1);

		ImGui::BeginGroup();
		ImGui::Image(GetImage("arrow_right16")->GetBackendID(), ImVec2(16, 16));
		ImGui::SameLine();
		if (ImGui::Selectable("General", selected == 0))
			selected = 0;
		ImGui::EndGroup();

		ImGui::BeginGroup();
		ImGui::Image(GetImage("arrow_right16")->GetBackendID(), ImVec2(16, 16));
		ImGui::SameLine();
		if (ImGui::Selectable("Rendering", selected == 1))
			selected = 1;
		ImGui::EndGroup();

		ImGui::BeginGroup();
		ImGui::Image(GetImage("arrow_right16")->GetBackendID(), ImVec2(16, 16));
		ImGui::SameLine();
		if (ImGui::Selectable("Input", selected == 2))
			selected = 2;
		ImGui::EndGroup();

		ImGui::EndChild();

		ImGui::SameLine();

		// zone droite (contenu)
		ImGui::BeginChild("right", ImVec2(0, 0), true);

		switch (selected)
		{
			case 0:
			{
				TitleIcon("Windows", GetImage("windows64"));

				const char* filters[1] = { "*.ico" };
				FileInput(iconBuffer, 256, "Game icon", "",1, filters,"Windows ico files", "A default icon will be used");

				ImGui::PushFont(getFont("desc"));
				ImGui::TextColored(COLOR_DESC, "The icon of the executable and the window");
				ImGui::PopFont();


				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();
				TitleIcon("Linux", GetImage("linux64"));
				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();
				editor::TitleIcon("MacOS", GetImage("apple64"));

				break;
			}


			case 1:
			{
				ComboBox("Graphics Backend", backends, IM_ARRAYSIZE(backends));

				break;
			}

			case 2:
			{
				break;
			}
		}

		ImGui::EndChild();

		ImGui::PopFont();
	}
}

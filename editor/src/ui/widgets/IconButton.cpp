#include "IconButton.h"

#include "../Image.h"
#include "../common.h"
#include <imgui/imgui.h>


namespace editor
{
	void IconButton(const char *_tooltip, Image *_image, float _sizex, float _sizey)
	{
		ImGui::ImageButton(_tooltip, _image->GetBackendID(), ImVec2(_sizex,_sizey), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
		if (ImGui::IsItemHovered())
		{
			ImGui::PushFont(getFont("std"));
			ImGui::BeginTooltip();
			ImGui::Text(_tooltip);
			ImGui::EndTooltip();
			ImGui::PopFont();
		}
	}
}

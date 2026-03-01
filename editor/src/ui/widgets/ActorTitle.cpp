#include "ActorTitle.h"

#include "../common.h"
#include <imgui/imgui.h>

#include "ui/Image.h"

namespace editor
{
	void ActorTitle(const char* _name)
	{
		ImGui::Image(GetImage("generic-actor64")->GetBackendID(), ImVec2(64,64), GL_UV_REVERSED);
		ImGui::PushFont(getFont("std"));
		ImGui::SameLine();
		ImGui::Text(_name);
		ImGui::PopFont();
	}
}
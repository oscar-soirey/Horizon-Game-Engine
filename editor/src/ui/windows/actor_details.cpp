#include "actor_details.h"

#include "../common.h"
#include <imgui/imgui.h>

#include <hge/core/actor.h>


namespace editor
{
	ActorDetails::ActorDetails()
	{
		title = "Actor Details";
	}

	//!!!!!
	//CRASH car selected actors contient des dangling pointer, solution : clear selected actors à la fermeture
	//!!!!!
	void ActorDetails::content()
	{
		ImGui::PushFont(getFont("std"));

		ImVec2 space = ImGui::GetContentRegionAvail();

		ImGui::BeginChild("ScrollBox", space, false);

		for (auto* a : editor::selected_actors_)
		{
			if (a)
			{
				for (const auto& [name, value] : a->GetProperties())
				{
					ImGui::Text("%s", name.c_str());

					ImGui::SameLine();

					std::string inputid = "##" + a->object_id_ + name;
					char buffer[256] = {};
					//copy the current content
					strncpy(buffer, hge::PropertyToString(value).c_str(), sizeof(buffer) - 1);

					//only if modified
					if (ImGui::InputText(inputid.c_str(), buffer, 256))
					{
						a->SetPropertyValueStr(name.c_str(), buffer);
					}

					ImGui::Separator();
				}
			}
		}

		ImGui::EndChild();

		ImGui::PopFont();
	}
}

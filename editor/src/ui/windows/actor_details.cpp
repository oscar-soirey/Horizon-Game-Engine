#include "actor_details.h"

#include "../common.h"
#include "../widgets/ComboBox.h"
#include "../widgets/Details.h"
#include <imgui/imgui.h>

#include <hge/core/actor.h>

#include "hge/core/engine.h"
#include "hge/core/level.h"

#include <string>
#include <sstream>

struct PropertyMeta {
	std::string section;
	std::string name;
};

// Capitalize first letter, lowercase the rest
static std::string Capitalize(const std::string& s) {
	if (s.empty()) return s;
	std::string out = s;
	out[0] = std::toupper(out[0]);
	for (size_t i = 1; i < out.size(); i++)
		out[i] = std::tolower(out[i]);
	return out;
}

// "_physics_gravity_scale" → { "Physics", "Gravity Scale" }
static PropertyMeta ParsePropertyKey(const std::string& key) {
	// Split by '_', skip leading empty token
	std::vector<std::string> tokens;
	std::stringstream ss(key);
	std::string token;
	while (std::getline(ss, token, '_'))
		if (!token.empty())
			tokens.push_back(token);

	PropertyMeta meta;
	if (tokens.empty()) return meta;

	bool hasSection = !key.empty() && key[0] == '_';

	if (hasSection) {
		meta.section = Capitalize(tokens[0]);
		for (size_t i = 1; i < tokens.size(); i++) {
			if (i > 1) meta.name += ' ';
			meta.name += Capitalize(tokens[i]);
		}
	} else {
		for (size_t i = 0; i < tokens.size(); i++) {
			if (i > 0) meta.name += ' ';
			meta.name += Capitalize(tokens[i]);
		}
	}

	return meta;
}


namespace editor
{
	void SwitchPropType(const std::string& inputid, hge::HGE_Object* a, const std::string& name, hge::HGE_Property value)
	{
		switch (value.GetType())
		{
			case 0:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<int>(name.c_str());
				if (DetailInt(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 1:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<float>(name.c_str());
				if (DetailFloat(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 2:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<bool>(name.c_str());
				if (DetailBool(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 3:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<std::string>(name.c_str());
				if (DetailString(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 4:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<HGE_Vec2>(name.c_str());
				if (DetailVec2(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 5:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<HGE_Vec3>(name.c_str());
				if (DetailVec3(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 6:
			{
				ImGui::SameLine();
				auto buf = a->GetPropertyValue<HGE_Vec4>(name.c_str());
				if (DetailVec4(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			case 7:
			{
				auto buf = a->GetPropertyValue<HGE_Transform>(name.c_str());
				if (DetailTransform(inputid.c_str(), buf))
				{
					a->SetPropertyValue(name.c_str(), buf);
				}
				break;
			}
			default: break;
		}
	}


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
					if (value.access == hge::Exposed)
					{
						auto meta = ParsePropertyKey(name);

						//remplacer par une vraie section
						std::string complete_cache_name;
						if (meta.section.empty()) complete_cache_name = meta.name;
						else complete_cache_name = meta.section + " : " + meta.name;

						ImGui::Text("%s", complete_cache_name.c_str());
						std::string inputid = "##" + a->object_id_ + name;
						SwitchPropType(inputid, a, name, value);

						ImGui::Separator();
					}
				}
				for (const auto& [id, comp] : a->GetComponents())
				{
					if (ImGui::CollapsingHeader(id.c_str()))
					{
						//for each attributes of component
						for (const auto& [name, value] : comp.get()->GetProperties())
						{
							auto meta = ParsePropertyKey(name);

							//remplacer par une vraie section
							std::string complete_cache_name;
							if (meta.section.empty()) complete_cache_name = meta.name;
							else complete_cache_name = meta.section + " : " + meta.name;

							ImGui::Text("%s", complete_cache_name.c_str());
							std::string inputid = "##" + a->object_id_ + id + name;
							SwitchPropType(inputid, comp.get(), name, value);
						}
					}
				}
			}
			float btn_size_x = ImGui::GetContentRegionAvail().x;
			if (ImGui::Button("Delete Actor", ImVec2(btn_size_x, 34)))
			{
				std::erase(actors_, a);
				selected_actors_.clear();
				hge::GetCurrentLevel()->DestroyActor(a);
			}
		}

		ImGui::EndChild();

		ImGui::PopFont();
	}
}

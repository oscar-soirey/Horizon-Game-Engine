#include "Details.h"

#include <imgui/imgui.h>
#include <cstring>

const char* boolean[2]{"false", "true"};

namespace editor
{
	bool DetailInt(const char *label, int &ref)
	{
		bool changed = false;

		changed |= ImGui::InputInt((label + std::string(label)).c_str(), &ref);

		/** Drag input désactivé temporairement
		ImGui::SameLine();
		std::string drag_label_buff = "##_drag" + std::string(label);
		changed |= ImGui::DragInt(drag_label_buff.c_str(), &ref, 0.1f);
		*/

		return changed;
	}

	bool DetailFloat(const char *label, float &ref)
	{
		return ImGui::InputFloat(label, &ref);
	}

	bool DetailBool(const char *label, bool &ref)
	{
		bool copy=ref;
		bool new_val=ref;

		if (ImGui::RadioButton("False", !new_val))
			new_val = false;

		ImGui::SameLine();

		if (ImGui::RadioButton("True", new_val))
			new_val = true;

		if (copy != new_val)
		{
			//changed
			ref = new_val;
			return true;
		}
		return false;
	}

	bool DetailString(const char *label, std::string &ref)
	{
		char buf[512];
		std::strncpy(buf, ref.c_str(), sizeof(buf));
		//null terminate
		buf[sizeof(buf)-1] = '\0';

		bool changed = ImGui::InputText(label, buf, 512, ImGuiInputTextFlags_EnterReturnsTrue);
		if (changed)
		{
			ref = buf;
		}
		return changed;
	}

	bool DetailVec2(const char *label, HGE_Vec2 &ref)
	{
		return ImGui::DragFloat2(label, &ref.x, 0.2f);
	}

	bool DetailVec3(const char *label, HGE_Vec3 &ref)
	{
		return ImGui::DragFloat3(label, &ref.x, 0.2f);
	}

	bool DetailVec4(const char *label, HGE_Vec4 &ref)
	{
		return ImGui::DragFloat4(label, &ref.x, 0.2f);
	}

	bool DetailTransform(const char *label, HGE_Transform &ref)
	{
		bool changed=false;

		ImGui::TextColored(ImVec4(0.8f, 0.f, 0.f, 1.f), "Location : ");
		ImGui::SameLine();
		std::string loc_label = "##_location" + std::string(label);
		changed |= ImGui::DragFloat3(loc_label.c_str(), &ref.location_.x, 0.2f);

		ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.f, 1.f), "Rotation : ");
		ImGui::SameLine();
		std::string rot_label = "##_rotation" + std::string(label);
		changed |= ImGui::DragFloat3(rot_label.c_str(), &ref.rotation_.x, 0.2f);

		ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.f, 1.f), "Scale : ");
		ImGui::SameLine();
		std::string scale_label = "##_scale" + std::string(label);
		changed |= ImGui::DragFloat3(scale_label.c_str(), &ref.scale_.x, 0.2f);

		return changed;
	}
}
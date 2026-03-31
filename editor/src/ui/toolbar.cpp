#include "toolbar.h"

#include <hge/core/engine.h>
#include <hge/core/level.h>
#include <hge/core/actor.h>
#include <hge/core/typename.h>

#include <imgui/imgui.h>
#include <tinyxml2/tinyxml2.h>

#include <type_traits>

#include "widgets/IconButton.h"
#include "common.h"

void SaveLevel()
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument doc;
	doc.InsertFirstChild(doc.NewDeclaration());

	//root element
	XMLElement* root = doc.NewElement("Level");
	doc.InsertEndChild(root);

	//add children
	for (const auto* a : hge::GetCurrentLevel()->GetActors())
	{
		//find actor class name
		std::string classname = hge::ETypeName(*a);
		XMLElement* actor = doc.NewElement(classname.c_str());

		//for each properties
		for (const auto& [name, p] : a->GetProperties())
		{
			actor->SetAttribute(name.c_str(), hge::PropertyToString(p).c_str());
		}

		//for each components
		for (const auto& [id, comp] : a->GetComponents())
		{
			XMLElement* comp_child_elem = doc.NewElement(id.c_str());
			//for each attributes of the component
			for (const auto& [name, p] : comp.get()->GetProperties())
			{
				comp_child_elem->SetAttribute(name.c_str(), hge::PropertyToString(p).c_str());
			}
			actor->InsertEndChild(comp_child_elem);
		}

		root->InsertEndChild(actor);
	}

	doc.SaveFile(editor::current_level_file_.c_str());

	ImGui::OpenPopup("LevelSaved");
}

namespace editor
{
	void ShowToolbar()
	{
		float toolbar_height = 48.f;
		ImGui::BeginChild("Toolbar", ImVec2(0.f, toolbar_height), false);
		{
			if (IconButton("Save level", GetImage("save64"), 32.f, 32.f))
			{
				SaveLevel();
			}
			ImGui::SameLine();

			if (IconButton("Build Release", GetImage("build64"), 32.f, 32.f)) { printf("Build C++ project\n"); }
			ImGui::SameLine();

			if (IconButton("Play in editor", GetImage("play64"),32.f,32.f))
			{
				editor::update_physics = !update_physics;
			}
			ImGui::SameLine();

			if (IconButton("Reload modules", GetImage("reload64"),32.f,32.f))
			{
				editor::OpenProjectEditor(nullptr);
			}


			if (ImGui::BeginPopup("LevelSaved"))
			{
				ImGui::Text("Level Saved with success");

				ImGui::EndPopup();
			}
		}
		ImGui::EndChild();
	}
}
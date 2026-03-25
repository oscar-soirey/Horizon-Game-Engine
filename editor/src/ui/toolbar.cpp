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
	printf("save level current level : %s\n", editor::current_level_file_.c_str());

	using namespace tinyxml2;
	tinyxml2::XMLDocument doc;
	doc.InsertFirstChild(doc.NewDeclaration());

	//root element
	XMLElement* root = doc.NewElement("Level");
	doc.InsertEndChild(root);
	//set level attributes
	root->SetAttribute("name", "Level_01");
	root->SetAttribute("version", 1);

	//add children
	for (const auto* a : hge::GetCurrentLevel()->GetActors())
	{
		//find actor class name
		std::string classname = hge::GetTypeName<std::remove_reference_t<decltype(*a)>>();
		XMLElement* actor = doc.NewElement(classname.c_str());
		for (const auto& [name, p] : a->GetProperties())
		{
			actor->SetAttribute(name.c_str(), hge::PropertyToString(p).c_str());
		}
		root->InsertEndChild(actor);
	}

	doc.SaveFile(editor::current_level_file_.c_str());
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

			if (IconButton("Play in editor", GetImage("play64"),32.f,32.f)) { printf("Play in editor\n"); }
			ImGui::SameLine();

			if (IconButton("Reload modules", GetImage("reload64"),32.f,32.f)) { printf("Reload modules\n"); }
		}
		ImGui::EndChild();
	}
}
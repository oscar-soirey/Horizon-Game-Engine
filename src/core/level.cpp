//
// Created by User on 28/01/2026.
//

#include "level.h"

#include "log.h"
#include "actor.h"
#include "engine.h"
#include <modules/factory.h>

#include <tinyxml2/tinyxml2.h>
#include <thread>
#include <algorithm>

#include "typename.h"

namespace hge
{
	HGE_Level::~HGE_Level()
	{
		for (const auto& a : actors_)
		{
			delete a;
		}
		actors_.clear();
	}

	void HGE_Level::LoadFromFile(const char *_path)
	{
		using namespace tinyxml2;

		tinyxml2::XMLDocument doc;
		XMLError eResult = doc.LoadFile(_path);
		if (eResult != XML_SUCCESS)
		{
			LOG_ERROR("error while reading level file");
			return;
		}

		XMLElement* root = doc.RootElement();  //level tag
		if (!root)
		{
			LOG_ERROR("no <level> tag");
			return;
		}

		//each actor elements
		for (XMLElement* actor = root->FirstChildElement();
			actor != nullptr;
			actor = actor->NextSiblingElement()
		)
		{

			//find constructor actor
			std::string type_name = actor->Name();  //name of the actor class, eg. Player, Character
			auto ctor = gamefactory::GetObjectConstructor(type_name.c_str());
			if (!ctor)
			{
				LOG_ERROR("actor not found in factory");
				continue;
			}

			//construct actor
			auto* obj = (HGE_Actor*)ctor();
			if (!obj)
			{
				LOG_ERROR("constructor error");
				continue;
			}

			//pass the scene backend id
			obj->backend_scene_id_ = GetEngineHRL_SceneID();

			//initialize each attributes
			const XMLAttribute* attr = actor->FirstAttribute();
			while (attr)
			{
				if (obj->PropertyExists(attr->Name()))
				{
					obj->SetPropertyValueStr(attr->Name(), attr->Value());
				}
				else
				{
					LOG_ERROR("Property doesnt exists");
				}

				attr = attr->Next();
			}

			//init before manipulate components (components created at init function)
			obj->Init();

			//while components
			const XMLElement* comp = actor->FirstChildElement();
			while (comp)
			{
				HGE_Component* comp_obj = obj->GetComponent(comp->Name());
				if (!comp_obj)
				{
					LOG_ERROR("Level file loading error : Component does not exist");
					comp = comp->NextSiblingElement();
					continue;
				}

				//while attributes of component
				const XMLAttribute* comp_attr = comp->FirstAttribute();
				while (comp_attr)
				{
					comp_obj->SetPropertyValueStr(comp_attr->Name(), comp_attr->Value());
					comp_attr = comp_attr->Next();
				}
				comp = comp->NextSiblingElement();
			}

			//add the actor ptr to the vector of the level
			actors_.emplace_back(obj);
		}
	}

	const std::vector<HGE_Actor *> &HGE_Level::GetActors() const
	{
		return actors_;
	}

	HGE_Actor* HGE_Level::SpawnActor(const char* _className)
	{
		HGE_Object* obj = gamefactory::GetObjectConstructor(_className)();
		auto* act = dynamic_cast<HGE_Actor*>(obj);

		if (!act)
		{
			LOG_ERROR("Try to spawn actor but class is not derived of HGE_Actor");
			return nullptr;
		}

		act->backend_scene_id_ = GetEngineHRL_SceneID();
		act->Init();
		actors_.push_back(act);

		return act;
	}

	void HGE_Level::DestroyActor(HGE_Actor *_act)
	{
		delete _act;
		std::erase(actors_, _act);
	}

	int HGE_Level::CountActorsOfClass(const char* _className) const
	{
		return std::count_if(actors_.begin(), actors_.end(), [_className](HGE_Actor* a)
		{
			//changer la Player brut par une fonction ClassName
			return std::strcmp(ETypeName(*a).c_str(), _className) == 0;
		});
	}
}

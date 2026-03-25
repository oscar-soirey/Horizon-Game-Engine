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

namespace hge
{
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

			obj->Init();

			//add the actor ptr to the vector of the level
			actors_.emplace_back(obj);
		}


		LOG_INFO("level loaded");
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

	int HGE_Level::CountActorsOfClass(const char* _className) const
	{
		return std::count_if(actors_.begin(), actors_.end(), [_className](HGE_Actor* a)
		{
			//changer la Player brut par une fonction ClassName
			return std::strcmp(/*a->ClassName()*/ "Player", _className) == 0;
		});
	}
}

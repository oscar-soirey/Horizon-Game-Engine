#include "actor.h"

namespace hge
{
	HGE_Actor::HGE_Actor()
	{
		HPROPERTY(transform_, Exposed);
	}

	void HGE_Actor::Tick(double _dt)
	{
		//update tous les components
		for (const auto& [key, comp] : components_)
		{
			comp->Tick(_dt);
		}
	}

	HGE_Vec3 HGE_Actor::GetAcceleration() const
	{
		return {};
	}

	HGE_Component* HGE_Actor::AddComponent(const char *_name, const std::function<std::unique_ptr<HGE_Component>()>& _constructor)
	{
		std::unique_ptr<HGE_Component> uniqueComp = _constructor();
		HGE_Component* ptrComp = uniqueComp.get();
		//on initialise le parent du comp avec this
		ptrComp->parent_ = this;
		//ptrComp->Init();
		components_.emplace(_name, std::move(uniqueComp));
		return ptrComp;
	}

	unsigned int HGE_Actor::BackendGetSceneID() const
	{
		return backend_scene_id_;
	}

}
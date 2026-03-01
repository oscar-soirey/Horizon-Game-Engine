#include "actor.h"

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

HGE_CBase* HGE_Actor::AddComponent(const char *_name, const std::function<std::unique_ptr<HGE_CBase>()>& _constructor)
{
	std::unique_ptr<HGE_CBase> uniqueComp = _constructor();
	HGE_CBase* ptrComp = uniqueComp.get();
	components_.emplace(_name, std::move(uniqueComp));
	return ptrComp;
}

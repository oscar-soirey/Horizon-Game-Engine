#include "light.h"

#include <hrl/hrl.h>
#include <core/actor.h>

struct BackendLight {
	HRL_id light = HRL_InvalidID;  //default value
};

namespace hge
{
	HGE_Light::HGE_Light() : backend_(new BackendLight())
	{
		HPROPERTY(color_, Exposed);
		HPROPERTY(attenuation_, Exposed);
		HPROPERTY(intensity_, Exposed);
	}

	HGE_Light::~HGE_Light()
	{
		HRL_DeleteLight(backend_->light);
		delete backend_;
	}

	void HGE_Light::Init()
	{
		backend_->light = HRL_CreateLight(parent_->BackendGetSceneID(), HRL_PointLight);
		printf("light id : %u\n", backend_->light);

		HRL_SetLightColor(backend_->light, color_.x, color_.y, color_.z);
		HRL_SetLightAttenuation(backend_->light, attenuation_);
		HRL_SetLightIntensity(backend_->light, intensity_);
	}


	void HGE_Light::LocationModified(HGE_Vec3 _loc)
	{
		if (backend_->light == HRL_InvalidID)
		{
			LOG_ERROR("Try to call HGE_Light::LocationModified, but Init was never called\n");
			return;
		}
		HRL_SetLightLocation(backend_->light, _loc.x, _loc.y, _loc.z);
	}

	void HGE_Light::RotationModified(HGE_Vec3 _rot)
	{
		if (backend_->light == HRL_InvalidID)
		{
			LOG_ERROR("Try to call HGE_Light::RotationModified, but Init was never called\n");
			return;
		}
		HRL_SetLightRotation(backend_->light, _rot.x, _rot.y, _rot.z);
	}
}
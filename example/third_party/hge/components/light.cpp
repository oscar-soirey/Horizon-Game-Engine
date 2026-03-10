#include "light.h"

#include <hrl/hrl.h>

#include "../core/private/engine_backend.h"

struct BackendLight {
	HRL_id light;
};

namespace hge
{
	HGE_Light::HGE_Light() : backend_(new BackendLight())
	{
		HPROPERTY(color_, Exposed);
		HPROPERTY(attenuation_, Exposed);
		HPROPERTY(intensity_, Exposed);

		backend_->light = HRL_CreateLight(priv::GetEngineHRL_SceneID(), HRL_PointLight);
	}

	HGE_Light::~HGE_Light()
	{
		HRL_DeleteLight(backend_->light);
		delete backend_;
	}

	void HGE_Light::Init()
	{
		HRL_SetLightColor(backend_->light, color_.x, color_.y, color_.z);
		HRL_SetLightAttenuation(backend_->light, attenuation_);
		HRL_SetLightIntensity(backend_->light, intensity_);
	}


	void HGE_Light::LocationModified(HGE_Vec3 _loc)
	{
		HRL_SetLightLocation(backend_->light, _loc.x, _loc.y, _loc.z);
	}

	void HGE_Light::RotationModified(HGE_Vec3 _rot)
	{
		HRL_SetLightRotation(backend_->light, _rot.x, _rot.y, _rot.z);
	}
}
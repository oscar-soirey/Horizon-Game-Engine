#include "sprite.h"

#include <hrl/hrl.h>

#include "../core/private/runtime_ressources.h"
#include "core/actor.h"
#include "glm/detail/type_mat2x3.hpp"

struct BackendSprite {
	HRL_id sprite;
};

namespace hge
{
	HGE_Sprite::HGE_Sprite() : backend_(new BackendSprite())
	{
		HPROPERTY(material_, Exposed);
	}

	HGE_Sprite::~HGE_Sprite()
	{
		HRL_DeleteMesh(backend_->sprite);
		delete backend_;
	}

	void HGE_Sprite::Init()
	{
		backend_->sprite = HRL_CreateMesh(parent_->BackendGetSceneID(), HRL_Sprite);
		SetRelativeTransform(HGE_Transform());

		std::string materialString = material_.string();
		HRL_SetMeshMaterial(backend_->sprite, priv::runtime_ressources::AddMaterial(materialString.c_str()));
	}

	void HGE_Sprite::LocationModified(HGE_Vec3 _loc)
	{
		HRL_SetMeshLocation(backend_->sprite, _loc.x, _loc.y, _loc.z);
	}

	void HGE_Sprite::RotationModified(HGE_Vec3 _rot)
	{
		HRL_SetMeshRotation(backend_->sprite, _rot.x, _rot.y, _rot.z);
	}

	void HGE_Sprite::ScaleModified(HGE_Vec3 _scale)
	{
		HRL_SetMeshScale(backend_->sprite, _scale.x, _scale.y, _scale.z);
	}
}
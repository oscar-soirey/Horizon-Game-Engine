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
		HPROPERTY(material, Exposed);
	}

	HGE_Sprite::~HGE_Sprite()
	{
		HRL_DeleteMesh(backend_->sprite);
		delete backend_;
	}

	void HGE_Sprite::Init()
	{
		backend_->sprite = HRL_CreateMesh(parent_->BackendGetSceneID(), HRL_Sprite);

		std::string materialString = material.string();
		HRL_SetMeshMaterial(backend_->sprite, priv::runtime_ressources::AddMaterial(materialString.c_str()));
	}

	void HGE_Sprite::TransformModified()
	{
		HRL_SetMeshLocation(backend_->sprite, GetAbsoluteLocation().x,  GetAbsoluteLocation().y,  GetAbsoluteLocation().z);
		HRL_SetMeshRotation(backend_->sprite, GetAbsoluteRotation().x, GetAbsoluteRotation().y, GetAbsoluteRotation().z);
		HRL_SetMeshScale(backend_->sprite, GetAbsoluteScale().x, GetAbsoluteScale().y, GetAbsoluteScale().z);
	}
}
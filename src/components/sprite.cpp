#include "sprite.h"

#include "../core/private/runtime_ressources.h"
#include "core/actor.h"

#include <hrl/hrl.h>
#include <glm/detail/type_mat2x3.hpp>
#include <box2d/box2d.h>

struct BackendSprite {
	HRL_id sprite;
};

namespace hge
{
	HGE_Sprite::HGE_Sprite(HGE_Actor* _parent) : HGE_SceneComponent(_parent), backend_(new BackendSprite())
	{
		HPROPERTY(material, Exposed, MaterialModified());

		backend_->sprite = HRL_CreateMesh(parent_->BackendGetSceneID(), HRL_Sprite);

		//subscribe to transform modified and physics mode changed
		parent_->ED_transform_modified.Subscribe([this](){ TransformModified(); });
		parent_->ED_physics_mode_changed.Subscribe([this](){ PhysicsModeChanged(); });
	}

	HGE_Sprite::~HGE_Sprite()
	{
		HRL_DeleteMesh(backend_->sprite);
		delete backend_;
	}

	void HGE_Sprite::TransformModified()
	{
		HRL_SetMeshLocation(backend_->sprite, GetAbsoluteLocation().x,  GetAbsoluteLocation().y,  GetAbsoluteLocation().z);
		HRL_SetMeshRotation(backend_->sprite, GetAbsoluteRotation().x, GetAbsoluteRotation().y, GetAbsoluteRotation().z);
		HRL_SetMeshScale(backend_->sprite, GetAbsoluteScale().x, GetAbsoluteScale().y, GetAbsoluteScale().z);
	}

	void HGE_Sprite::PhysicsModeChanged()
	{
		if (parent_->physics_mode != NONE)
		{
			b2Polygon box = b2MakeBox(1.f, 1.f);
			b2ShapeDef shape_def = b2DefaultShapeDef();
			shape_def.density = 1.0f;

			b2ShapeId shape_id = b2CreatePolygonShape(*parent_->GetRigidBody(), &shape_def, &box);

			b2Shape_SetFriction(shape_id, 1.f);  //friction
			b2Shape_SetRestitution(shape_id, 0.2f);  //rebond
		}
	}


	void HGE_Sprite::MaterialModified()
	{
		HRL_SetMeshMaterial(backend_->sprite, priv::runtime_ressources::AddMaterial(material.c_str()));
	}
}
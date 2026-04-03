#include "sprite.h"

#include "../core/private/runtime_ressources.h"
#include "core/actor.h"

#include <hrl/hrl.h>
#include <box2d/box2d.h>

struct BackendSprite {
	HRL_id sprite;
};

namespace hge
{
	HGE_Sprite::HGE_Sprite(HGE_Actor* _parent) : HGE_SceneComponent(_parent), backend_(new BackendSprite())
	{
		HPROPERTY(material, Exposed, MaterialModified());

		HPROPERTY(_physics_shape, Exposed, PhysicsChanged());
		HPROPERTY(_physics_box_size, Exposed, PhysicsChanged());
		HPROPERTY(_physics_density, Exposed, PhysicsChanged());
		HPROPERTY(_physics_friction, Exposed, PhysicsChanged());
		HPROPERTY(_physics_bounciness, Exposed, PhysicsChanged());
		HPROPERTY(_physics_capsule_height, Exposed, PhysicsChanged());
		HPROPERTY(_physics_capsule_radius, Exposed, PhysicsChanged());

		backend_->sprite = HRL_CreateMeshSprite(parent_->BackendGetSceneID());

		//subscribe to transform modified and physics mode changed
		parent_->ED_transform_modified.Subscribe([this]{ TransformModified(); });
		parent_->ED_physics_mode_changed.Subscribe([this]{ PhysicsChanged(); });
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

	void HGE_Sprite::PhysicsChanged()
	{
		if (parent_->_physics_mode != NONE)
		{
			b2ShapeId shape_id;

			switch (_physics_shape)
			{
				using enum physics::EShapes;
				case Box:
				{
					b2Polygon polygon_shape = b2MakeBox(_physics_box_size.x, _physics_box_size.y);
					b2ShapeDef shape_def = b2DefaultShapeDef();
					shape_def.density = _physics_density;

					shape_id = b2CreatePolygonShape(*parent_->GetRigidBody(), &shape_def, &polygon_shape);

					break;
				}
				case Square:
				{
					//polygon_shape = b2MakeSquare()
					break;
				}
				case Capsule:
				{
					b2Capsule capsule{
						{0.f, -_physics_capsule_height/2 },
						{ 0.f, _physics_capsule_height/2 },
						_physics_capsule_radius
					};

					b2ShapeDef shape_def = b2DefaultShapeDef();
					shape_id = b2CreateCapsuleShape(*parent_->GetRigidBody(), &shape_def, &capsule);
				}
				default: break;
			}

			b2Shape_SetFriction(shape_id, _physics_friction);
			b2Shape_SetRestitution(shape_id, _physics_bounciness);
		}
	}


	void HGE_Sprite::MaterialModified()
	{
		HRL_SetMeshMaterial(backend_->sprite, priv::runtime_ressources::AddMaterial(material.c_str()));
	}
}
#ifndef HGE_SPRITE_COMPONENT_H
#define HGE_SPRITE_COMPONENT_H

#include "scene_component.h"
#include "../physics/shapes.h"

struct BackendSprite;

namespace hge
{
	class ENGINE_API HGE_Sprite : public HGE_SceneComponent {
	public:
		std::string material;

		//passer une data structure (ou une section) physics au lieu de tout réécrire a chaque fois
		int _physics_shape = physics::EShapes::Capsule;
		HGE_Vec2 _physics_box_size{1.f};

		float _physics_capsule_height=1.5f;
		float _physics_capsule_radius=0.4f;

		float _physics_density=1.f;
		float _physics_friction=1.f;
		float _physics_bounciness=0.f;


		explicit HGE_Sprite(HGE_Actor* _parent);
		~HGE_Sprite() override;

	private:
		BackendSprite* backend_=nullptr;

		void MaterialModified();

		void TransformModified() override;
		void PhysicsChanged();
	};
}

#endif

#ifndef HGE_SPRITE_COMPONENT_H
#define HGE_SPRITE_COMPONENT_H

#include "scene_component.h"

struct BackendSprite;

namespace hge
{
	class HGE_Sprite : public HGE_SceneComponent {
	public:
		HGE_Path material_;

		HGE_Sprite();
		~HGE_Sprite() override;

		void Init() override;

	private:
		BackendSprite* backend_;

	protected:
		void LocationModified(HGE_Vec3 _loc) override;
		void RotationModified(HGE_Vec3 _rot) override;
		void ScaleModified(HGE_Vec3 _scale) override;
	};
}

#endif

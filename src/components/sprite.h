#ifndef HGE_SPRITE_COMPONENT_H
#define HGE_SPRITE_COMPONENT_H

#include "scene_component.h"

struct BackendSprite;

namespace hge
{
	class ENGINE_API HGE_Sprite : public HGE_SceneComponent {
	public:
		HGE_Path material;

		HGE_Sprite();
		~HGE_Sprite() override;

		void Init() override;

	private:
		BackendSprite* backend_;

	protected:
		void TransformModified() override;
	};
}

#endif

#ifndef HGE_LIGHT_COMPONENT_H
#define HGE_LIGHT_COMPONENT_H

#include "scene_component.h"

struct BackendLight;

namespace hge
{
	class ENGINE_API HGE_Light : public HGE_SceneComponent {
	public:
		HGE_Vec3 color_;
		float attenuation_;
		float intensity_;


		HGE_Light();
		~HGE_Light() override;

		void Init() override;

	private:
		BackendLight* backend_;

	protected:
		void TransformModified() override;
	};
}

#endif
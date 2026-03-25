#ifndef HGE_BASE_TCOMPONENT_H
#define HGE_BASE_TCOMPONENT_H

#include "base_component.h"

namespace hge
{
	class ENGINE_API HGE_SceneComponent : public HGE_Component {
		//to call TransformModified()
		friend class HGE_Actor;

	public:
		HGE_Transform relative_transform{};

		HGE_SceneComponent();

		HGE_Transform GetAbsoluteTransform();
		HGE_Vec3 GetAbsoluteLocation();
		HGE_Vec3 GetAbsoluteRotation();
		HGE_Vec3 GetAbsoluteScale();

	protected:
		//called when relative transform was modified and parent actor transform modified
		virtual void TransformModified(){}
	};
}

#endif
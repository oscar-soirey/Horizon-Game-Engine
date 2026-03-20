#ifndef HGE_BASE_TCOMPONENT_H
#define HGE_BASE_TCOMPONENT_H

#include "base_component.h"

namespace hge
{
	class ENGINE_API HGE_SceneComponent : public HGE_Component {
	public:
		void SetRelativeTransform(HGE_Transform _transform);
		void SetRelativeLocation(HGE_Vec3 _location);
		void SetRelativeRotation(HGE_Vec3 _rotation);
		void SetRelativeScale(HGE_Vec3 _scale);

		HGE_Transform GetRelativeTransform();
		HGE_Transform GetAbsoluteTransform();

		HGE_Vec3 GetRelativeLocation();
		HGE_Vec3 GetAbsoluteLocation();

		HGE_Vec3 GetRelativeRotation();
		HGE_Vec3 GetAbsoluteRotation();

		HGE_Vec3 GetRelativeScale();
		HGE_Vec3 GetAbsoluteScale();

	protected:
		virtual void LocationModified(HGE_Vec3 _loc) {}
		virtual void RotationModified(HGE_Vec3 _rot) {}
		virtual void ScaleModified(HGE_Vec3 _scale) {}

	private:
		HGE_Transform transform_{};
	};
}

#endif
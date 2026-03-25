#ifndef HGE_CAMERA_COMPONENT_H
#define HGE_CAMERA_COMPONENT_H

#include "scene_component.h"

struct BackendCamera;

namespace hge
{
	typedef enum {
		Perspective,
		Orthographic
	}Camera_Type_e;

	class ENGINE_API HGE_Camera : public HGE_SceneComponent {
	public:
		HGE_Camera();
		~HGE_Camera() override;

		void Init() override;

		void SetType(Camera_Type_e _type);
		Camera_Type_e GetType() const;
		void SetPerspectiveFov(float _fov);
		float GetPerspectiveFov() const;
		void SetOrthoHeight(float _height);
		float GetOrthoHeight() const;

	private:
		BackendCamera* backend_;

	protected:
		void TransformModified() override;
	};
}

#endif
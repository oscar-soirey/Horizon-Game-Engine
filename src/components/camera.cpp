#include "camera.h"

#include <hrl/hrl.h>
#include <core/actor.h>

struct BackendCamera {
	HRL_id cam;
	hge::Camera_Type_e type;
	float fov;
	float ortho_height;
};


namespace hge
{
	HGE_Camera::HGE_Camera() : backend_(new BackendCamera()) {}

	HGE_Camera::~HGE_Camera()
	{
		HRL_DeleteCamera(backend_->cam);
		delete backend_;
	}

	void HGE_Camera::Init()
	{
		backend_->cam = HRL_CreateCamera(parent_->BackendGetSceneID(), HRL_Perspective);
		backend_->type = Perspective;
		backend_->fov = 60.0f;
		backend_->ortho_height = 1000.f;

		HRL_SetCameraPerspectiveFov(backend_->cam, backend_->fov);
		HRL_SetCameraNearPlane(backend_->cam, 0.001f);
		HRL_SetCameraFarPlane(backend_->cam, 10000.f);
	}

	void HGE_Camera::SetType(Camera_Type_e _type)
	{
		HRL_uint type = HRL_Ortho;
		if (_type == Perspective) type = HRL_Perspective;

		HRL_SetCameraType(backend_->cam, type);
		backend_->type = _type;
		if (_type == Perspective)
		{
			HRL_SetCameraPerspectiveFov(backend_->cam, backend_->fov);
		}
		else
		{
			//si y'a un bug ca vient peut etre du near plane, qui doit être en ortho négatif (-10000; 10000) exemple
			HRL_SetCameraOrthoVertical(backend_->cam, backend_->ortho_height);
		}
	}

	Camera_Type_e HGE_Camera::GetType() const
	{
		return backend_->type;
	}

	void HGE_Camera::SetPerspectiveFov(float _fov)
	{
		if (backend_->type == Orthographic)
		{
			LOG_ERROR("SetPerspectiveFov error : camera is not perspective");
			return;
		}
		backend_->fov = _fov;
		HRL_SetCameraPerspectiveFov(backend_->cam, _fov);
	}

	float HGE_Camera::GetPerspectiveFov() const
	{
		if (backend_->type != Perspective)
		{
			LOG_ERROR("GetPerspectiveFov error : camera is not perspective");
			return 0.0f;
		}

		return backend_->fov;
	}

	void HGE_Camera::SetOrthoHeight(float _height)
	{
		if (backend_->type != Orthographic)
		{
			LOG_ERROR("SetOrthoHeight error : camera is not orthographic");
			return;
		}

		backend_->ortho_height = _height;
		HRL_SetCameraOrthoVertical(backend_->cam, _height);
	}

	float HGE_Camera::GetOrthoHeight() const
	{
		if (backend_->type != Orthographic)
		{
			LOG_ERROR("GetOrthoHeight error : camera is not orthographic");
			return 0.0f;
		}

		return backend_->ortho_height;
	}

	void HGE_Camera::LocationModified(HGE_Vec3 _loc)
	{
		HRL_SetCameraPosition(backend_->cam, _loc.x, _loc.y, _loc.z);
	}

	void HGE_Camera::RotationModified(HGE_Vec3 _rot)
	{
		HRL_SetCameraRotation(backend_->cam, _rot.x, _rot.y, _rot.z);
	}
}
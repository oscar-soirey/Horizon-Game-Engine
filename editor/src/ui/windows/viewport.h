#pragma once

#include "../window.h"
#include <hrl/hrl.h>
#include <hge/core/common.h>

namespace editor
{
	class Viewport : public Window {
	public:
		explicit Viewport(HRL_id _scene);

	private:
		void content() final;
		void Logic(double _dt) final;
		void ResizeCallback(int _width, int _height) final;

		bool mouseCaptured = false;
		HRL_id hrl_scene_;
		HRL_id hrl_cam_;

		//logic cache
		bool firstMouse = false;
		double lastMouseX, lastMouseY;

		HGE_Vec3 camera_position_{};
		HGE_Vec3 camera_rotation_{};

		float cameraSpeed = 5.0f;
		float mouseSensitivity = 0.1f;
	};
}

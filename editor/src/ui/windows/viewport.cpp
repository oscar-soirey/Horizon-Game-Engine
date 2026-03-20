#include "viewport.h"

#include "ui/common.h"

#include <imgui/imgui.h>

#include <hrl/hrl.h>
#include <hrl/hrl_gl.h>

#include <GLFW/glfw3.h>

#include "hge/core/engine.h"

extern GLFWwindow* mainWin;

namespace editor
{
	Viewport::Viewport(HRL_id _scene) : hrl_scene_(_scene)
	{
		title = "Viewport";
		hrl_cam_ = HRL_CreateCamera(_scene, HRL_Perspective);
		HRL_SetCameraPerspectiveFov(hrl_cam_, 60.f);
		HRL_SetCameraFarPlane(hrl_cam_, 10000.f);
		HRL_CreateViewport(_scene, hrl_cam_, 0.f, 0.f, 1.f, 1.f);
	}

	void Viewport::Logic(double _dt)
	{
		if (mouseCaptured)
		{
			//on recentre la souris dans la fenêtre pour éviter un gros jump
			//
			//

			double mouseX, mouseY;
			glfwGetCursorPos(mainWin, &mouseX, &mouseY);

			if (firstMouse)
			{
				lastMouseX = mouseX;
				lastMouseY = mouseY;
				firstMouse = false;
			}

			float offsetX = (float)(mouseX - lastMouseX) * mouseSensitivity;
			float offsetY = (float)(lastMouseY - mouseY) * mouseSensitivity;

			lastMouseX = mouseX;
			lastMouseY = mouseY;

			camera_rotation_.y += offsetX;
			camera_rotation_.x += offsetY;

			//clamp pitch pour éviter de regarder trop haut/bas
			if (camera_rotation_.x > 89.0f) camera_rotation_.x = 89.0f;
			if (camera_rotation_.x < -89.0f) camera_rotation_.x = -89.0f;

			HRL_SetCameraRotation(hrl_cam_, camera_rotation_.x, camera_rotation_.y, 0.0f);

			HGE_Vec3 camFront = HGE_GetForwardVector(camera_rotation_);
			HGE_Vec3 camRight = HGE_GetRightVector(camera_rotation_);
			HGE_Vec3 camUp = HGE_GetUpVector(camera_rotation_);

			if (glfwGetKey(mainWin, GLFW_KEY_W) == GLFW_PRESS) camera_position_ += camFront * cameraSpeed * (float)_dt;
			if (glfwGetKey(mainWin, GLFW_KEY_S) == GLFW_PRESS) camera_position_ -= camFront * cameraSpeed * (float)_dt;
			if (glfwGetKey(mainWin, GLFW_KEY_A) == GLFW_PRESS) camera_position_ -= camRight * cameraSpeed * (float)_dt;
			if (glfwGetKey(mainWin, GLFW_KEY_D) == GLFW_PRESS) camera_position_ += camRight * cameraSpeed * (float)_dt;
			if (glfwGetKey(mainWin, GLFW_KEY_E) == GLFW_PRESS) camera_position_ += camUp * cameraSpeed * (float)_dt;
			if (glfwGetKey(mainWin, GLFW_KEY_Q) == GLFW_PRESS) camera_position_ -= camUp * cameraSpeed * (float)_dt;

			HRL_SetCameraPosition(hrl_cam_, camera_position_.x, camera_position_.y, camera_position_.z);
		}
	}


	void Viewport::content()
	{
		ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::Image(HRL_GL_GetSceneTextureGL_ID(hrl_scene_), size, GL_UV_REVERSED);

		if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			if (!mouseCaptured)
			{
				firstMouse = true;
			}
			glfwSetInputMode(mainWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouseCaptured = true;
		}
		else if (mouseCaptured)
		{
			glfwSetInputMode(mainWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseCaptured = false;
		}
	}

	void Viewport::ResizeCallback(int _width, int _height)
	{
		HRL_id scene = hge::GetEngineHRL_SceneID();
		HRL_ResizeSceneTexture(scene, _width, _height);
	}

}

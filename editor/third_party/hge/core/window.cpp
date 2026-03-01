#include "window.h"

#include "log.h"
#include "../filesystem/filesystem.h"

#include <glfw/glfw3.h>

//STB_IMAGE_IMPLEMENTATION déja définit dans HRL
#include <stb_image.h>

#include <memory>


HGE_GLFW_Window::~HGE_GLFW_Window()
{
	if (win_)
	{
		glfwDestroyWindow(win_);
	}
	glfwTerminate();
}
void HGE_GLFW_Window::Init(int width, int height, const char *title, const char *icon, std::function<void(int width, int height)> resizeCallback)
{
	glfwInit();
	win_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(win_);
	glfwSetFramebufferSizeCallback(win_, [](GLFWwindow* window, int w, int h)
	{
			auto self = reinterpret_cast<HGE_GLFW_Window*>(glfwGetWindowUserPointer(window));
			if (self && self->resizeCallback_)
				self->resizeCallback_(w, h);
	});
	glfwSetWindowUserPointer(win_, this);
}

void HGE_GLFW_Window::PollEvents()
{
	glfwPollEvents();
}
void HGE_GLFW_Window::SwapBuffers()
{
	glfwSwapBuffers(win_);
}
bool HGE_GLFW_Window::ShouldClose() const
{
	return glfwWindowShouldClose(win_);
}
void *HGE_GLFW_Window::GetNativeLoader()
{
	return (void*)glfwGetProcAddress;
}

double HGE_GLFW_Window::GetDeltaTime() const
{
	return 0.0;
}

int HGE_GLFW_Window::GetWidth() const
{
	return 0;
}

int HGE_GLFW_Window::GetHeight() const
{
	return 0;
}

void HGE_GLFW_Window::SetWidth()
{

}

void HGE_GLFW_Window::SetHeight()
{

}

int HGE_GLFW_Window::SetIcon(const char *_path)
{
	size_t imageSize;
	std::string imageData = HGE_filesystem::HGE_GetFileContent(_path, &imageSize, false);

	//si l'image ou la taille est invalide
	if (imageData.empty() || imageSize == 0)
	{
		LOG_ERROR("Window set icon failed: error while reading image of size : " + std::to_string(imageSize) + "o");
		return -1;
	}

	//on charge l'image avec stb, puis on change l'icone glfw
	int w, h, channels;
	unsigned char* pixels = stbi_load_from_memory(
		(stbi_uc*)imageData.c_str(),
		(int)imageSize,
		&w,
		&h,
		&channels,
		STBI_rgb_alpha);

	//on arrete si les pixels sont vides
	if (!pixels)
	{
		std::string failure = stbi_failure_reason();
		LOG_ERROR("Window set icon failed: error while reading image pixels" + failure);
		return -1;
	}

	//on crée l'objet image de glfw
	GLFWimage icon;
	icon.width = w;
	icon.height = h;
	icon.pixels = pixels;
	glfwSetWindowIcon(win_, 1, &icon);

	//on libere la mémoire allouée a stb
	stbi_image_free(pixels);

	return 0;
}

void HGE_GLFW_Window::SetVsyncActive(bool _active)
{
	glfwSwapInterval(_active);
}


GLFWwindow *HGE_GLFW_Window::GetGLFWwindow() const
{
	return win_;
}

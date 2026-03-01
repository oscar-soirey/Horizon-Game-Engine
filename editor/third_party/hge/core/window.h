#ifndef HGE_WINDOW_H
#define HGE_WINDOW_H

#include <functional>

//abstract window class
class HGE_Window {
public:
	HGE_Window()=default;
	virtual ~HGE_Window()=default;

	virtual void Init(int width, int height, const char* title, const char* icon, std::function<void(int width, int height)> resizeCallback) = 0;

	virtual void PollEvents() = 0;
	virtual void SwapBuffers() = 0;
	virtual bool ShouldClose() const = 0;
	virtual void* GetNativeLoader() = 0;
	virtual double GetDeltaTime() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void SetWidth() = 0;
	virtual void SetHeight() = 0;
	virtual int SetIcon(const char* _path) = 0;
	virtual void SetVsyncActive(bool _active) = 0;

	//ajouter des fonctions de contrôle comme SetSize, SetIcon, etc...
protected:
	std::function<void(int width, int height)> resizeCallback_;
};



//GLFW - OpenGL and Vulkan
class GLFWwindow;
class HGE_GLFW_Window final : public HGE_Window {
public:
	HGE_GLFW_Window() = default;
	~HGE_GLFW_Window() override;

	void Init(int width, int height, const char *title, const char *icon, std::function<void(int width, int height)> resizeCallback) override;

	void PollEvents() override;
	void SwapBuffers() override;
	bool ShouldClose() const override;
	void* GetNativeLoader() override;
	double GetDeltaTime() const override;
	int GetWidth() const override;
	int GetHeight() const override;

	void SetWidth() override;
	void SetHeight() override;
	int SetIcon(const char* _path) override;
	void SetVsyncActive(bool _active) override;

	GLFWwindow* GetGLFWwindow() const;

private:
	GLFWwindow* win_ = nullptr;
};




//WIN32 - DirectX


#endif

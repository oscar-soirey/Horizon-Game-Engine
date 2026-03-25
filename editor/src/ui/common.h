#pragma once

#include <filesystem>
#include <imgui/imgui.h>
#include <functional>
#include <memory>
#include <hge/filesystem/ini_parser.h>

#define INVERT_BOOL(var) var = !var

#define COLOR_DESC ImVec4(0.4f,0.4f,0.4f,0.8f)

#define EDITOR_WIN(__win__, __args__) []() { return std::make_unique<__win__>(__args__); }

#define GL_UV_REVERSED ImVec2(0.f, 1.f), ImVec2(1.f, 0.f)

namespace HGE_filesystem
{
	class HGE_Ini;
}

namespace hge
{
	class HGE_Actor;
}

namespace editor
{
	class Window;
	class Image;

	//options
	inline char** argv;

	//fonts
	ImFont* getFont(const char* _name);
	void addFont(const char* _name, const char* _path, float _size);

	//images
	Image* GetImage(const char* _name);
	void AddImage(const char* _name, const char* _path);

	//windows
	Window* GetWindow(const char* _name);
	void AddWindow(const char* _name, const std::function<std::unique_ptr<Window>()>&_window);
	bool DeleteWindow(const char* _name);
	const std::unordered_map<std::string, std::unique_ptr<Window>>& GetWindows();
	void SetWindowVisibility(bool _visible);

	//config
	hge::filesystem::HGE_Ini* GetConfigIni(const char* _name);
	void AddConfigIni(const char* _name, const char* _path);

	//Path
	std::filesystem::path GetExecutableDir();

	//project
	/**
	 * @param _path absolute path to the .hgeproj file
	 */
	void OpenProjectEditor(const char* _path);

	//level
	inline std::vector<hge::HGE_Actor*> actors_;
	inline std::vector<hge::HGE_Actor*> selected_actors_;
	inline std::string current_level_file_;
}

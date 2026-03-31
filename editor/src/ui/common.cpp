#include "common.h"

#include "window.h"
#include "Image.h"
#include "windows/content_browser.h"

#include <hge/filesystem/filesystem.h>
#include <hge/filesystem/ini_parser.h>
#include <hge/core/log.h>
#include <hge/modules/private/system_module.h>

#include <nlohmann/json.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>

#include "hge/core/engine.h"
#include "windows/place_actors.h"

namespace fs = std::filesystem;

namespace
{
	//on stocke les fonts imgui et les objets Image
	std::unordered_map<std::string, ImFont*> fonts_;

	//images
	std::unordered_map<std::string, std::unique_ptr<editor::Image>> images_;


	//windows
	std::unordered_map<std::string, std::unique_ptr<editor::Window>> windows_;

	//ini config files
	std::unordered_map<std::string, std::unique_ptr<hge::filesystem::HGE_Ini>> ini_config_files_;

	//project
	std::filesystem::path current_project_;
}

namespace editor
{
	ImFont *getFont(const char *_name)
	{
		auto it = fonts_.find(_name);
		if (it != fonts_.end())
		{
			return it->second;
		}
		else
		{
			LOG_ERROR("GetFont error : font doesnt exists");
			return nullptr;
		}
	}

	void addFont(const char* _name, const char *_path, float _size)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromFileTTF(_path, _size);
		if (font)
		{
			fonts_[_name] = font;
		}
		else
		{
			LOG_ERROR("AddFont error");
		}
	}


	Image *GetImage(const char *_name)
	{
		auto it = images_.find(_name);
		if (it != images_.end())
		{
			return it->second.get();
		}
		else
		{
			LOG_ERROR("GetImage error : font doesnt exists");
			return nullptr;
		}
	}

	void AddImage(const char *_name, const char *_path)
	{
		auto it = images_.find(_name);
		if (it != images_.end())
		{
			LOG_ERROR("AddImage error : image name already exists");
		}
		images_.emplace(_name, std::make_unique<Image>(_path));
	}


	Window *GetWindow(const char *_name)
	{
		auto it = windows_.find(_name);
		if (it != windows_.end())
		{
			return it->second.get();
		}
		else
		{
			LOG_ERROR("GetWindow error, window doesnt exists : " + std::string(_name));
			return nullptr;
		}
	}

	void AddWindow(const char* _name, const std::function<std::unique_ptr<Window>()>&_window)
	{
		auto it = windows_.find(_name);
		if (it != windows_.end())
		{
			LOG_ERROR("AddWindow error : win name already exists");
		}
		windows_.emplace(_name, _window());
	}

	const std::unordered_map<std::string, std::unique_ptr<Window>>& GetWindows()
	{
		return windows_;
	}


	hge::filesystem::HGE_Ini *GetConfigIni(const char *_name)
	{
		auto it = ini_config_files_.find(_name);
		if (it != ini_config_files_.end())
		{
			return it->second.get();
		}
		else
		{
			LOG_ERROR("GetConfigIni error : config file doesnt exists");
			return nullptr;
		}
	}

	void AddConfigIni(const char *_name, const char *_path)
	{
		auto it = ini_config_files_.find(_name);
		if (it != ini_config_files_.end())
		{
			LOG_ERROR("AddConfigIni error : file name already exists");
		}
		ini_config_files_.emplace(_name, std::make_unique<hge::filesystem::HGE_Ini>(_path));
	}

	std::filesystem::path GetExecutableDir()
	{
		std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
		std::filesystem::path exeDir = exePath.parent_path();
		return exeDir;
	}

	nlohmann::json LoadJson(const std::filesystem::path& path)
	{
		std::ifstream file(path);
		if (!file)
			throw std::runtime_error("Impossible d'ouvrir le fichier");

		nlohmann::json j;
		file >> j;
		return j;
	}

	static hge::module::Module* current_project_dll_=nullptr;

	void OpenProjectEditor(const char* _path)
	{
		//a project is still opened
		if (current_project_dll_)
		{
			hge::UnloadCurrentLevel();

			actors_.clear();
			selected_actors_.clear();

			//vider la factory
			hge::gamefactory::ClearFactory();

			delete current_project_dll_;
		}

		//if nullptr we want to reload the project, dont change the path
		if (_path!=nullptr)
		{
			current_project_ = _path;
		}
		fs::path root = current_project_.parent_path();

		size_t bufferSize;
		std::string buffer = hge::filesystem::GetFileContent(current_project_.string().c_str(), &bufferSize, true);
		nlohmann::json j;
		try
		{
			j = nlohmann::json::parse(buffer);
		}
		catch (const nlohmann::json::parse_error& e)
		{
			LOG_ERROR("Json project file parse error : " + std::string(e.what()));
			return;
		}

		fs::path packageDir = j.at("package-dir");
		fs::path buildDir = j.at("build-dir");

		auto* browser = static_cast<ContentBrowser*>(GetWindow("ContentBrowser"));
		browser->dir_ = root / packageDir;

		std::string modulePath = (root / buildDir / "libexample.dll").string();
		//on crée un nouveau objet Module avec new (tres important car le module doit rester chargé pendant tout le jeu)
		current_project_dll_ = new hge::module::Module();
		current_project_dll_->LoadShared(modulePath.c_str());
		current_project_dll_->InsertFactory();

		//on update la factory de la window place actors
		static_cast<PlaceActors*>(GetWindow("PlaceActors"))->project_factory_ = hge::gamefactory::GetFactory();
	}
}
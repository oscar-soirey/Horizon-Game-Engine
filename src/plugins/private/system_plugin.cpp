#include "system_plugin.h"

#include "../../core/log.h"
#include <filesystem>

namespace fs = std::filesystem;

std::string FindFirstDll(const fs::path& folder)
{
	for (const auto& entry : fs::directory_iterator(folder))
	{
		if (!entry.is_regular_file())
			continue;

		if (entry.path().extension() == ".dll")
			return entry.path().string();
	}

	//vide si rien trouvé
	return {};
}

namespace hge::sys_plugin
{
#ifdef _WIN32
	SysPlugin::SysPlugin(const char *parent_path)
	{
		//charger la dll
		std::filesystem::path fs_path = parent_path;

		std::string dll_path = FindFirstDll(fs_path);
		sysmodule_ = LoadLibraryA(dll_path.c_str());
		if (!sysmodule_)
		{
			LOG_ERROR("DLL plugin loading error : unable to load dll" + std::string(parent_path));
			return;
		}

		auto load_plugin_fn = (LoadPluginFn)GetProcAddress(sysmodule_, "LoadPlugin");
		plugin_ = load_plugin_fn();

		LOG_INFO("Plugin registered with success");
	}

#elifdef __linux__
	SysPlugin::SysPlugin(const char *parent_path)=0;
#elifdef __APPLE__
	SysPlugin::SysPlugin(const char *parent_path)=0;
#endif

#ifdef _WIN32
	SysPlugin::~SysPlugin()
	{
		LOG_WARNING("Plugin destructor called");
		FreeLibrary(sysmodule_);
	}
#elifdef __linux__
	SysPlugin::~SysPlugin()=0;
#elifdef __APPLE__
	SysPlugin::~SysPlugin()=0;
#endif

	IPlugin *SysPlugin::GetPlugin()
	{
		return plugin_;
	}

}
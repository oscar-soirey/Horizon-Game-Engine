#include "system_module.h"

#include "../../core/log.h"

namespace hge::module
{
#ifdef _WIN32
	Module::~Module()
	{
		LOG_WARNING("Module destructor called");
		module_factory_.clear();
		FreeLibrary(sysmodule_);
	}

	int Module::LoadShared(const char *_libpath)
	{
		//charger la dll
		sysmodule_ = LoadLibraryA(_libpath);
		if (!sysmodule_)
		{
			LOG_ERROR("DLL module loading error : unable to load dll" + std::string(_libpath));
			return -1;
		}

		//recuperer le pointeur vers la fonction FactoryRegisterClasses
		using RegisterFunc = std::unordered_map<std::string, factory::ObjectConstructor>(*)();
		RegisterFunc registerFunction = (RegisterFunc)GetProcAddress(sysmodule_, "FactoryRegisterClasses");
		if (!registerFunction)
		{
			LOG_ERROR("DLL module error : unable to find FactoryRegisterClasses function compiled" + std::string(_libpath));
			return -1;
		}

		//appeller la fonction
		module_factory_ = registerFunction();
		LOG_INFO("FactoryRegisterClasses called with success");

		return 0;
	}

#elifdef __linux__
	int Module::LoadShared(const char *_libpath)=0;
#elifdef __APPLE__
	int Module::LoadShared(const char *_libpath)=0;
#endif

	void Module::InsertFactory()
	{
		gamefactory::InsertFactory(module_factory_);
	}

}
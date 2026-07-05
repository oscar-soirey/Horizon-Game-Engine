/**
 *
 */

#ifndef HGE_SYSTEM_MODULE_H
#define HGE_SYSTEM_MODULE_H

#include "../factory.h"

#ifdef _WIN32
#include <Windows.h>
#define SYSTEM_MODULE HMODULE
#elifdef __linux__
#define SYSTEM_MODULE
#elifdef __APPLE__
#define SYSTEM_MODULE
#endif

namespace hge::module
{
	class ENGINE_API Module {
	public:
		Module()=default;
		~Module();

		int LoadShared(const char* _libpath);
		void InsertFactory();

	private:
		SYSTEM_MODULE sysmodule_;
		std::unordered_map<std::string, factory::ObjectConstructor> module_factory_;
	};
}

#endif
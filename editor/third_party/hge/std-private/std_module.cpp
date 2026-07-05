#include "std_module.h"

#include "modules/module.h"
#include "../std-private/light_actor.h"

std::unordered_map<std::string, hge::factory::ObjectConstructor> GetStdModule()
{
	std::unordered_map<std::string, hge::factory::ObjectConstructor> __factory__;

	//register every classes
	HGE_MODULE_REGISTER(ALight);

	//return factory
	return __factory__;
}
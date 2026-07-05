#ifndef HGE_MODULE_H
#define HGE_MODULE_H

#include "factory.h"

#define HGE_MODULE_FUNCTION extern "C" __declspec(dllexport)

//utilise la factory créée dans HGE_LINK_MODULE
#define HGE_MODULE_REGISTER(__class__) __factory__.emplace(#__class__, []() -> hge::HGE_Object* { return new __class__(); })

#define HGE_LINK_MODULE(__module_content__) extern "C" __declspec(dllexport) std::unordered_map<std::string, hge::factory::ObjectConstructor> FactoryRegisterClasses() \
{ std::unordered_map<std::string, hge::factory::ObjectConstructor> __factory__; \
__module_content__ \
return __factory__; }

#endif
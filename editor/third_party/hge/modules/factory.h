#ifndef HGE_FACTORY_H
#define HGE_FACTORY_H

#include "../core/object.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace hge
{

	namespace factory
	{
		using ObjectConstructor = std::function<std::unique_ptr<HGE_Object>()>;
		using Factory = std::unordered_map<std::string, ObjectConstructor>;
	}

	namespace gamefactory
	{
		//object factory
		factory::ObjectConstructor GetObjectConstructor(const char* _name);
		factory::Factory GetFactory();
		void InsertFactory(factory::Factory _moduleFactory);
	}

}

#endif
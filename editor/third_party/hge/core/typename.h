#ifndef HGE_TYPENAME_UTIL_H
#define HGE_TYPENAME_UTIL_H

#include <string>

namespace hge
{
	template <typename T>
	std::string GetTypeName()
	{
#ifdef _MSC_VER
		std::string name = __FUNCSIG__;
		auto start = name.find("getTypeName<") + 12;
		auto end = name.find(">(void)");
		return name.substr(start, end - start);
#else
		std::string name = __PRETTY_FUNCTION__;
		auto start = name.find("T = ") + 4;
		auto end = name.find(";");
		return name.substr(start, end - start);
#endif
	}
}

#endif
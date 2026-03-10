/**
 *
 */

#include "object.h"

#include <sstream>
#include <charconv>

hge::PropVariantType getValueByString(const std::string& value)
{
	//bool
	if (value == "true") return true;
	if (value == "false") return false;

	//int
	int intVal;
	if (auto [p, ec] = std::from_chars(value.data(), value.data() + value.size(), intVal);
		ec == std::errc() && p == value.data() + value.size())
		return intVal;

	//float
	try
	{
		size_t idx;
		float f = std::stof(value, &idx);
		if (idx == value.size()) return f;
	}
	catch (...) {}

	//vec2 "vec2:x,y"
	if (value.rfind("vec2:", 0) == 0)
	{
		std::string data = value.substr(5);
		size_t comma = data.find(',');
		if (comma != std::string::npos)
			return HGE_Vec2(std::stof(data.substr(0, comma)),
							 std::stof(data.substr(comma + 1)));
	}

	//vec3 "vec3:x,y,z"
	if (value.rfind("vec3:", 0) == 0)
	{
		std::string data = value.substr(5);
		size_t c1 = data.find(',');
		size_t c2 = data.rfind(',');
		if (c1 != std::string::npos && c2 != std::string::npos && c1 != c2)
			return HGE_Vec3(std::stof(data.substr(0, c1)),
							 std::stof(data.substr(c1 + 1, c2 - c1 - 1)),
							 std::stof(data.substr(c2 + 1)));
	}

	//vec4 "vec4:x,y,z,w"
	if (value.rfind("vec4:", 0) == 0)
	{
		std::string data = value.substr(5);
		size_t c1 = data.find(',');
		size_t c2 = data.find(',', c1 + 1);
		size_t c3 = data.rfind(',');
		if (c1 != std::string::npos && c2 != std::string::npos && c3 != std::string::npos)
			return HGE_Vec4(std::stof(data.substr(0, c1)),
							 std::stof(data.substr(c1 + 1, c2 - c1 - 1)),
							 std::stof(data.substr(c2 + 1, c3 - c2 - 1)),
							 std::stof(data.substr(c3 + 1)));
	}

	//transform
	if (value.rfind("transform:", 0) == 0)
	{
		std::string data = value.substr(10); //remove "transform:"

		//splitted by ';'
		size_t s1 = data.find(';');
		size_t s2 = data.find(';', s1 + 1);

		if (s1 != std::string::npos && s2 != std::string::npos)
		{
			auto parseVec3 = [](const std::string& str) -> HGE_Vec3
			{
				size_t c1 = str.find(',');
				size_t c2 = str.rfind(',');
				if (c1 != std::string::npos && c2 != std::string::npos)
				{
					return HGE_Vec3(
							std::stof(str.substr(0, c1)),
							std::stof(str.substr(c1 + 1, c2 - c1 - 1)),
							std::stof(str.substr(c2 + 1))
					);
				}
				//fallback if error
				return HGE_Vec3{};
			};

			HGE_Vec3 location = parseVec3(data.substr(0, s1));
			HGE_Vec3 rotation = parseVec3(data.substr(s1 + 1, s2 - s1 - 1));
			HGE_Vec3 scale    = parseVec3(data.substr(s2 + 1));

			return HGE_Transform{location, rotation, scale};
		}
	}

	//string if none
	return value;
}

namespace hge
{
	HGE_Object::HGE_Object()
	{
		HPROPERTY(object_id_, Exposed);
	}

	HGE_Object::~HGE_Object()=default;


	bool HGE_Object::PropertyExists(const char* _name)
	{
		auto it = properties_.find(_name);
		return it != properties_.end();
	}

	void HGE_Object::SetPropertyValueStr(const char* _name, const char* _val)
	{
		auto it = properties_.find(_name);
		if (it == properties_.end()) return;

		PropVariantType variant_val = getValueByString(_val);

		std::visit([&](auto* ptr){
			using T = std::remove_pointer_t<decltype(ptr)>;
			if (ptr) *ptr = std::get<T>(variant_val);
		}, it->second.property_member);
	}


	Access HGE_Object::GetPropertyAccess(const char* _name)
	{
		auto it = properties_.find(_name);
		if (it == properties_.end())
		{
			return {};
		}
		return it->second.access;
	}
}
/**
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#include "common.h"
#include "log.h"


enum Access {
	Exposed,
	Editable
};

using PropVariantType = std::variant<int, float, bool, std::string, HGE_Vec2, HGE_Vec3, HGE_Vec4, HGE_Transform>;
using PropVariantTypePtr = std::variant<int*, float*, bool*, std::string*, HGE_Vec2*, HGE_Vec3*, HGE_Vec4*, HGE_Transform*>;

typedef struct {
	PropVariantTypePtr property_member{};
	Access access{Exposed};
}HGE_Property;


class HGE_Object {
public:
	std::string object_id_;

	HGE_Object();
	virtual ~HGE_Object()=default;

	virtual void Init()=0;
	virtual void BeginPlay()=0;
	virtual void EndPlay()=0;
	virtual void Tick(double _dt)=0;

	template<typename T>
	T GetPropertyValue(const char* _name)
	{
		if (auto p = std::get_if<T*>(&properties_[_name].property_member))
		{
			return **p;
		}
		else
		{
			LOG_ERROR("GetPropertyValue, Error with property : " + std::string(_name));
			return T{};
		}
	}

	template<typename T>
	void SetPropertyValue(const char* _name, T _val)
	{
		if (auto p = std::get_if<T*>(&properties_[_name].property_member))
		{
			**p = _val;
		}
		else
		{
			LOG_ERROR("SetPropertyValue, Error with property : " + std::string(_name));
		}
	}

	bool PropertyExists(const char* _name);
	Access GetPropertyAccess(const char* _name);

protected:
	std::unordered_map<std::string, HGE_Property> properties_;
};


#define HPROPERTY(var, access) properties_[#var] = HGE_Property(&var, access)


#endif //OBJECT_H

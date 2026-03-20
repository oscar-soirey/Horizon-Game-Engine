/**
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <unordered_map>
#include <string>
#include <functional>

#include "common.h"
#include "log.h"
#include "build_dll.h"

namespace hge
{
	enum Access {
		Exposed,
		Editable
	};

	using PropVariantType = std::variant<int, float, bool, std::string, HGE_Vec2, HGE_Vec3, HGE_Vec4, HGE_Transform, HGE_Path>;
	using PropVariantTypePtr = std::variant<int*, float*, bool*, std::string*, HGE_Vec2*, HGE_Vec3*, HGE_Vec4*, HGE_Transform*, HGE_Path*>;

	typedef struct {
		PropVariantTypePtr property_member{};
		Access access{Exposed};
	}HGE_Property;


	class ENGINE_API HGE_Object {
	public:
		std::string object_id_;

		HGE_Object();
		virtual ~HGE_Object();

		virtual void Init(){}
		virtual void BeginPlay(){}
		virtual void EndPlay(){}
		virtual void Tick(double _dt){}

		template<typename T>
		T GetPropertyValue(const char* _name)
		{
			if (auto p = std::get_if<T*>(&properties_[_name].property_member))
			{
				return **p;
			}
			LOG_ERROR("GetPropertyValue, Error with property : " + std::string(_name));
			return T{};
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

		void SetPropertyValueStr(const char* _name, const char* _val);

		bool PropertyExists(const char* _name);
		Access GetPropertyAccess(const char* _name);

	protected:
		std::unordered_map<std::string, HGE_Property> properties_;
	};
}

#define HPROPERTY(var, access) properties_[#var] = hge::HGE_Property(&var, access)


#endif //OBJECT_H

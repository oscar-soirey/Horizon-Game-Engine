/**
 *
 */

#include "object.h"


HGE_Object::HGE_Object()
{
	HPROPERTY(object_id_, Exposed);
}

bool HGE_Object::PropertyExists(const char* _name)
{
	auto it = properties_.find(_name);
	return it != properties_.end();
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

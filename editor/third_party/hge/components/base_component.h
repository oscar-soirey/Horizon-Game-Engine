#ifndef HGE_BASE_COMPONENT_H
#define HGE_BASE_COMPONENT_H

#include "../core/object.h"

namespace hge
{
	class HGE_Actor;

	class HGE_Component : public HGE_Object {
	public:
		//allow actor to modify private members (util for modify parent_ member)
		friend class HGE_Actor;

		HGE_Component()=default;

	protected:
		HGE_Actor* parent_ = nullptr;
	};
}

#endif
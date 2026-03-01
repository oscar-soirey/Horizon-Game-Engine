#ifndef HGE_BASE_COMPONENT_H
#define HGE_BASE_COMPONENT_H

#include "../core/object.h"

class HGE_CBase : HGE_Object {
public:
	HGE_CBase();

	void Tick(double _dt) override=0;
};

#endif
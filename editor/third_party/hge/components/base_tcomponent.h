#ifndef HGE_BASE_TCOMPONENT_H
#define HGE_BASE_TCOMPONENT_H

#include "base_component.h"

template<bool Btransform3D>
class HGE_TBase : public HGE_CBase {
public:
	union
	{
		HGE_Transform transform3D_;
		HGE_2D_Transform transform2D_;
	};
	auto GetAbsoluteTransform();

private:
	bool transform_3D_ = Btransform3D;
};


#endif
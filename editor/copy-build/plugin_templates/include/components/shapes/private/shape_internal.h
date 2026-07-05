#pragma once

#include <box2d/box2d.h>

namespace hge::priv
{
	struct ShapeInternal {
		b2ShapeId shape_id = b2_nullShapeId;
	};
}
#ifndef HGE_DEBUG_DRAW_H
#define HGE_DEBUG_DRAW_H

#include "../../core/api/build_dll.h"

class b2DebugDraw;

namespace hge::physics::priv
{
	void InitDebugDraw();
	void ENGINE_API DebugDrawTick();
	b2DebugDraw* GetPhysicsDebugDrawPtr();

}


#endif
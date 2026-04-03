#ifndef HGE_DEBUG_DRAW_H
#define HGE_DEBUG_DRAW_H

class b2DebugDraw;

namespace hge::physics
{
	void InitDebugDraw();
	b2DebugDraw* GetPhysicsDebugDrawPtr();
}


#endif
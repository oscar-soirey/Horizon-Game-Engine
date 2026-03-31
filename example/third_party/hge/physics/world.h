#ifndef HGE_PHYSICS_WORLD_H
#define HGE_PHYSICS_WORLD_H

#include "../core/common.h"
class b2WorldId;

namespace hge::physics
{
	void InitPhysics();
	b2WorldId& GetWorld();

	void UpdateWorld(double _dt);

	void SetGlobalGravity(HGE_Vec2 _force);
}

#endif
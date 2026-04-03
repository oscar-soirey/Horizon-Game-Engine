#include "world.h"

#include <box2d/box2d.h>

#include "debug_draw.h"

static b2WorldId world;

namespace hge::physics
{
	void InitPhysics()
	{
		//create world
		b2WorldDef world_def = b2DefaultWorldDef();
		world_def.gravity = (b2Vec2){0.f, -9.81f};

		world = b2CreateWorld(&world_def);
	}

	b2WorldId &GetWorld()
	{
		return world;
	}

	void UpdateWorld(double _dt, bool _drawDebug)
	{
		b2World_Step(world, (float)_dt, 4);
		if (_drawDebug)
		{
			b2World_Draw(world, GetPhysicsDebugDrawPtr());
		}
	}


	void SetGlobalGravity(HGE_Vec2 _force)
	{
		b2Vec2 new_gravity(_force.x, _force.y);
		b2World_SetGravity(world, new_gravity);
	}
}
#include "debug_draw.h"

#include "../world.h"
#include "core/engine.h"

#include <box2d/box2d.h>

#include <cstring>

static b2DebugDraw debug_draw;

#define CREATE_COLOR(color) \
	float r = ((color >> 16) & 0xFF) / 255.0f; \
	float g = ((color >> 8)  & 0xFF) / 255.0f; \
	float b = ((color >> 0)  & 0xFF) / 255.0f;

void HGE_DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	//remplacer les coordonnées z par les coordonées z du parent
	//HRL_DrawDebugSegment(hge::GetEngineHRL_SceneID(), p1.x, p1.y, 0.f, p2.x, p2.y, 0.f, r, g, b);
}

void HGE_DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	//paste data from box2d to HRL format
	std::vector<float> v_x(vertexCount);
	std::vector<float> v_y(vertexCount);
	for (int i = 0; i < vertexCount; i++)
	{
		v_x[i] = vertices[i].x;
		v_y[i] = vertices[i].y;
	}

	//init every z vertices to 0
	std::vector<float> v_z(vertexCount);
	memset(v_z.data(), 0, sizeof(float) * vertexCount);

	/*HRL_DrawDebugPolygon(hge::GetEngineHRL_SceneID(), HRL_DEBUG_HOLLOW,
		v_x.data(), v_y.data(), v_z.data(),
		vertexCount,
		r, g, b
	);*/
}

void HGE_DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount,
											float radius, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	//paste data from box2d to HRL format
	std::vector<float> v_x(vertexCount);
	std::vector<float> v_y(vertexCount);
	for (int i = 0; i < vertexCount; i++)
	{
		b2Vec2 world = b2TransformPoint(transform, vertices[i]);
		v_x[i] = world.x;
		v_y[i] = world.y;
	}

	//init every z vertices to 0
	std::vector<float> v_z(vertexCount);
	memset(v_z.data(), 0, sizeof(float) * vertexCount);

	/*HRL_DrawDebugPolygon(hge::GetEngineHRL_SceneID(), HRL_DEBUG_SOLID,
		v_x.data(), v_y.data(), v_z.data(),
		vertexCount,
		r, g, b
	);*/
}

void HGE_DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	/*HRL_DrawDebugCircle(hge::GetEngineHRL_SceneID(), HRL_DEBUG_HOLLOW,
		center.x, center.y, 0.f,
		radius, 32,
		r, g, b
	);*/
}

void HGE_DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	/*HRL_DrawDebugCircle(hge::GetEngineHRL_SceneID(), HRL_DEBUG_HOLLOW,
		transform.p.x, transform.p.y, 0.f,
		radius, 32,
		r, g, b
	);*/
}

void HGE_DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	/*HRL_DrawDebugCapsule(hge::GetEngineHRL_SceneID(), HRL_DEBUG_SOLID,
		p1.x, p1.y, 0.f,
		p2.x, p2.y, 0.f,
		radius, 32,
		r, g, b
	);*/
}

void HGE_DrawTransform(b2Transform transform, void* context)
{

}

void HGE_DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context)
{
	CREATE_COLOR(color);

	/*HRL_DrawDebugPoint(hge::GetEngineHRL_SceneID(),
		p.x, p.y, 0.f,
		size,
		r, g, b
	);*/
}

void HGE_DrawString(b2Vec2 p, const char* s, b2HexColor color, void* context)
{

}

namespace hge::physics::priv
{
	void InitDebugDraw()
	{
		debug_draw = b2DefaultDebugDraw();
		debug_draw.context = nullptr;

		debug_draw.drawShapes         = true;
		debug_draw.drawJoints         = true;
		debug_draw.drawMass           = true;
		debug_draw.drawContacts       = true;
		debug_draw.drawContactNormals = true;
		debug_draw.drawContactImpulses= true;

		debug_draw.DrawSegmentFcn = HGE_DrawSegment;
		debug_draw.DrawPolygonFcn = HGE_DrawPolygon;
		debug_draw.DrawSolidPolygonFcn = HGE_DrawSolidPolygon;
		debug_draw.DrawCircleFcn = HGE_DrawCircle;
		debug_draw.DrawSolidCircleFcn = HGE_DrawSolidCircle;
		debug_draw.DrawSolidCapsuleFcn = HGE_DrawSolidCapsule;
		debug_draw.DrawTransformFcn = HGE_DrawTransform;
		debug_draw.DrawPointFcn = HGE_DrawPoint;
		debug_draw.DrawStringFcn = HGE_DrawString;
	}

	void DebugDrawTick()
	{
		b2World_Draw(GetWorld(), GetPhysicsDebugDrawPtr());
	}

	b2DebugDraw *GetPhysicsDebugDrawPtr()
	{
		return &debug_draw;
	}
}
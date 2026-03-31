#pragma once

#include <hge/core/actor.h>

class Player : public hge::HGE_Actor {
public:
	int life=100;
	float fattr=0.f;
	bool battr=true;
	std::string sattr="hello world";
	HGE_Vec2 v2attr{};
	HGE_Vec3 v3attr{};
	HGE_Vec4 v4attr{};

	Player();
	void Init() override;
	void Tick(double _dt) override;
};
#pragma once

#include <hge/core/actor.h>

class Player : public hge::HGE_Actor {
public:
	int life=100;

	Player();
	void Init() override;
	void Tick(double _dt) override;
};
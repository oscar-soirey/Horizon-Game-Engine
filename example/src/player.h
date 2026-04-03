#pragma once

#include <hge/core/actor.h>

#include <hge/core/input.h>

class Player : public hge::HGE_Actor {
public:
	int life=100;

	Player();
	void Init() override;

private:
	void ProcessInput(double dt) override;

	hge::InputAction jump_action_ = "jump";
};
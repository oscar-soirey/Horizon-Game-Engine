#pragma once

#include <hge/core/character.h>

#include <hge/core/gameplay/input.h>

class Player : public hge::HGE_Character {
public:
	int life=100;

	Player();
	void Init() override;

private:
	void ProcessInput(double dt) override;

	hge::InputAction jump_action_ = "jump";
	hge::InputAxis1D move_x_axis_ = "move_x";
};
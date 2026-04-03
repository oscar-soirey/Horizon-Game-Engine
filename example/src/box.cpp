#include "box.h"

#include <hge/components/sprite.h>

Box::Box() {}

void Box::Init()
{
	auto* sprite = HCOMPONENT("sprite_comp", hge::HGE_Sprite);
	sprite->material = "S:/Horizon/game_engine/3.0/example/package/mat.mat";
}

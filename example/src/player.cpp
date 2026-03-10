#include "player.h"
#include <hge/components/camera.h>
#include <hge/components/sprite.h>
#include <hge/components/light.h>

Player::Player()
{
	HPROPERTY(life_, hge::Exposed);
}

void Player::Init()
{
	auto* cam = HCOMPONENT("cam_comp", hge::HGE_Camera);
	cam->Init();

	auto* sprite = HCOMPONENT("sprite_comp", hge::HGE_Sprite);
	sprite->material_ = "mat";
	sprite->Init();

	auto* light = HCOMPONENT("light_comp", hge::HGE_Light);
	light->color_ = HGE_Vec3(1,1,1);
	light->attenuation_ = 0.02f;
	light->intensity_ = 5.f;
	light->Init();
}
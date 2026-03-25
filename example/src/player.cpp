#include "player.h"

#include <hge/components/camera.h>
#include <hge/components/sprite.h>
#include <hge/components/light.h>
#include <hge/core/log.h>

Player::Player()
{
	HPROPERTY(life, hge::Exposed);
}

void Player::Init()
{
	auto* cam = HCOMPONENT("cam_comp", hge::HGE_Camera);
	cam->Init();

	auto* sprite = HCOMPONENT("sprite_comp", hge::HGE_Sprite);
	sprite->material = "S:/Horizon/game_engine/3.0/example/package/mat.mat";
	sprite->Init();
	sprite->relative_transform.scale_ = 25.f;

	auto* light = HCOMPONENT("light_comp", hge::HGE_Light);
	light->color_ = HGE_Vec3(1,1,1);
	light->attenuation_ = 0.02f;
	light->intensity_ = 5.f;
	light->relative_transform.location_ = HGE_Vec3(10.f, 10.f, 10.f);
	light->Init();
}

void Player::Tick(double _dt)
{
	HGE_Actor::Tick(_dt);
}


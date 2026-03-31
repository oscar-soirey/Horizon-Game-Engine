#include "light_actor.h"

void ALight::Init()
{
	light_comp = HCOMPONENT("light_comp", hge::HGE_Light);
	light_comp->color_ = HGE_Vec3(1,1,1);
	light_comp->attenuation_ = 0.02f;
	light_comp->intensity_ = 5.f;
	light_comp->relative_transform.location_ = HGE_Vec3(10.f, 10.f, 10.f);
}
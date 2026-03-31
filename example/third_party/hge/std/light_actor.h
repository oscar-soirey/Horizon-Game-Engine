#pragma once

#include "../core/actor.h"
#include "../core/build_dll.h"
#include "../components/light.h"

class ENGINE_API ALight : public hge::HGE_Actor {
public:
	ALight();
	~ALight();

	void Init() override;

	hge::HGE_Light* light_comp=nullptr;
};
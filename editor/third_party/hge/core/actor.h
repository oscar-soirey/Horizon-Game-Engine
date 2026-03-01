/**
 *
 */

#ifndef ACTOR_H
#define ACTOR_H

#include "object.h"
#include "common.h"
#include "../components/base_component.h"

#include <functional>
#include <memory>

class HGE_Actor : public HGE_Object {
public:
	HGE_Transform transform_{};

	HGE_Actor();
	~HGE_Actor() override;

	void Tick(double _dt) override;

	HGE_CBase* AddComponent(const char* _name, const std::function<std::unique_ptr<HGE_CBase>()>& _constructor);

	HGE_Vec3 GetAcceleration() const;

private:
	std::unordered_map<std::string, std::unique_ptr<HGE_CBase>> components_;

	HGE_Vec3 velocity_last_frame_;
	HGE_Vec3 velocity_;
};


#define HCOMPONENT(__name__, __class__) \
	static_cast<__class__*>(AddComponent(__name__, []{ return std::make_unique<__class__>(); }))


#endif
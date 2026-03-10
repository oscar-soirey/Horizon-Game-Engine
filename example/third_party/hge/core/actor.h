/**
 *
 */

#ifndef HGE_ACTOR_H
#define HGE_ACTOR_H

#include "object.h"
#include "common.h"
#include "../components/base_component.h"

#include <functional>
#include <memory>

namespace hge
{
	class HGE_Actor : public HGE_Object {
	public:
		HGE_Transform transform_{};

		HGE_Actor();

		void Tick(double _dt) override;

		HGE_Component* AddComponent(const char* _name, const std::function<std::unique_ptr<HGE_Component>()>& _constructor);

		HGE_Vec3 GetAcceleration() const;

	private:
		std::unordered_map<std::string, std::unique_ptr<HGE_Component>> components_;

		HGE_Vec3 velocity_last_frame_;
		HGE_Vec3 velocity_;
	};
}

#define HCOMPONENT(__name__, __class__) \
	dynamic_cast<__class__*>(AddComponent(__name__, []{ return std::make_unique<__class__>(); }))


#endif
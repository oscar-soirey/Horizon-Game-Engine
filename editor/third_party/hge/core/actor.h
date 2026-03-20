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
	class ENGINE_API HGE_Actor : public HGE_Object {
	public:
		friend class HGE_Level;

		HGE_Transform transform_{};

		HGE_Actor();

		void Tick(double _dt) override;

		HGE_Component* AddComponent(const char* _name, const std::function<std::unique_ptr<HGE_Component>()>& _constructor);

		HGE_Vec3 GetAcceleration() const;

		unsigned int BackendGetSceneID() const;

	private:
		std::unordered_map<std::string, std::unique_ptr<HGE_Component>> components_;

		HGE_Vec3 velocity_last_frame_;
		HGE_Vec3 velocity_;

		//backend information, do not modify
		unsigned int backend_scene_id_;
	};
}

/**
 * display name,
 * class typename,
 * instructions before call init
 */
#define HCOMPONENT(__name__, __class__) \
	dynamic_cast<__class__*>(AddComponent(__name__, []{ return std::make_unique<__class__>(); }))


#endif
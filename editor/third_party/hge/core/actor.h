/**
 *
 */

#ifndef HGE_ACTOR_H
#define HGE_ACTOR_H

#include "object.h"
#include "common.h"
#include "data/event_dispatcher.h"
#include "../components/base_component.h"

#include <functional>
#include <memory>

class b2BodyId;

typedef enum {
	NONE,
	STATIC,
	DYNAMIC,
	KINEMATIC
}HGE_PhysicsMode;

namespace hge
{
	class ENGINE_API HGE_Actor : public HGE_Object {
		friend class HGE_Level;
	public:
		HGE_Transform transform{};
		int physics_mode = DYNAMIC;

		HGE_Actor();
		void Tick(double _dt) override;

		HGE_Component* AddComponent(const char* _name, const std::function<std::unique_ptr<HGE_Component>(HGE_Actor*)>& _constructor);
		const std::unordered_map<std::string, std::unique_ptr<HGE_Component>>& GetComponents() const;
		HGE_Component* GetComponent(const char* _name);

		HGE_Vec3 GetAcceleration() const;

		unsigned int BackendGetSceneID() const;

		//physics
		b2BodyId* GetRigidBody();

		//usefull for notify components
		HEventDispatcher<> ED_transform_modified;
		HEventDispatcher<> ED_physics_mode_changed;

	private:
		std::unordered_map<std::string, std::unique_ptr<HGE_Component>> components_;

		void OnTransformChanged();
		void OnPhysicsModeChanged();

		//backend information, do not modify
		unsigned int backend_scene_id_;

		//physics handle ptr
		void* phys_hnd_=nullptr;

		HGE_Transform transform_last_frame_{};
	};
}

/**
 * display name,
 * class typename,
 * instructions before call init
 */
#define HCOMPONENT(__name__, __class__) \
	dynamic_cast<__class__*>(AddComponent(__name__, [ this ]( HGE_Actor* parent ){ return std::make_unique<__class__>(parent); }))


#endif
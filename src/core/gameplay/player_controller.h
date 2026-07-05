#ifndef HGE_PLAYER_CONTROLLER_H
#define HGE_PLAYER_CONTROLLER_H

#include "../api/build_dll.h"
#include <cstdint>

namespace hge
{
	class HGE_Actor;

	/**
	 * Create player controller
	 * @return ID of the new PlayerController
	 */
	int ENGINE_API CreatePlayer();
	void ENGINE_API DeletePlayer(int pc);
	void ENGINE_API PossessActor(int pc, HGE_Actor* act);
	void ENGINE_API UnpossessActor(int pc);
	ENGINE_API HGE_Actor* GetPossessedActor(int pc);

	//ajouter une gestion auto
	void ENGINE_API SetPlayerViewportSize(int pc,
		float x, float y,
		float _width, float _height
	);
	uint32_t GetPlayerViewportBackend(int pc);

	int ENGINE_API GetPlayerCount();
}

#endif
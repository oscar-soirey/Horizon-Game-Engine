#ifndef HGE_PLAYER_CONTROLLER_H
#define HGE_PLAYER_CONTROLLER_H

#include "build_dll.h"

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
	HGE_Actor* ENGINE_API GetPossessedActor(int pc);

	int ENGINE_API GetPlayerCount();
}

#endif
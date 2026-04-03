#include "player_controller.h"
#include "actor.h"

static int internal_player_id=0;

typedef struct {
	hge::HGE_Actor* possessed_actor_=nullptr;
}player_controller_t;

static std::unordered_map<int, player_controller_t> controllers;



namespace hge
{

	int CreatePlayer()
	{
		int new_id = internal_player_id++;
		controllers.emplace(new_id, player_controller_t());
		return new_id;
	}

	void DeletePlayer(int pc)
	{
		auto it = controllers.find(pc);
		if (it == controllers.end())
		{
			LOG_ERROR("DeletePlayer, invalid id");
			return;
		}
		controllers.erase(it);
	}


	void PossessActor(int pc, HGE_Actor *act)
	{
		auto it = controllers.find(pc);
		if (it == controllers.end())
		{
			LOG_ERROR("PossessActor, invalid id");
			return;
		}
		it->second.possessed_actor_ = act;
	}

	void UnpossessActor(int pc)
	{
		auto it = controllers.find(pc);
		if (it == controllers.end())
		{
			LOG_ERROR("UnpossessActor, invalid id");
			return;
		}
		it->second.possessed_actor_ = nullptr;
	}

	HGE_Actor *GetPossessedActor(int pc)
	{
		auto it = controllers.find(pc);
		if (it == controllers.end())
		{
			LOG_ERROR("GetPossessedActor, invalid id");
			return nullptr;
		}
		return it->second.possessed_actor_;
	}

	int GetPlayerCount()
	{
		return controllers.size();
	}
}

void PlayerControllersTick(double dt)
{
	for (const auto& c : controllers)
	{
		if (c.second.possessed_actor_)
		{
			c.second.possessed_actor_->ProcessInput(dt);
		}
	}
}
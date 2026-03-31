#include "engine.h"

#include <cassert>

#include "private/engine_backend.h"

#include "actor.h"
#include "level.h"

#include "../filesystem/filesystem.h"
#include "../filesystem/ini_parser.h"

#include <vector>
#include <thread>

#include <hrl/hrl.h>

#include "modules/factory.h"
#include "std-private/std_module.h"
#include "../physics/world.h"


typedef struct {
	//graphics
	int backend;

	//window
	int width;
	int height;
	std::string title;
	std::string iconPath;
}config_structure_t;
static config_structure_t config;


static bool gameRunning;

static uint32_t hrl_scene_id;

//the current opened level
static hge::HGE_Level* current_level_;

namespace hge
{
	void InitEngine(uint32_t _mode, const char* _configPath, void* _loader, bool _renderOnScreen)
	{
		gameRunning = true;

		//init le filesystem
		filesystem::InitFilesystem(_mode == HGE_PREVIEW);

		//on utilise pas le filesystem car on utilise toujours un raw file
		filesystem::HGE_Ini configIni(_configPath);

		config.backend = configIni.Get<int>("RenderingBackend");

		HRL_Init(config.backend);
		HRL_InitContext(config.width, config.height, _loader);

		hrl_scene_id = HRL_CreateScene(_renderOnScreen);

		gamefactory::InsertFactory(GetStdModule());

		physics::InitPhysics();
	}


	int EngineRunning() { return gameRunning; }
	void QuitEngine()
	{
		gameRunning = false;
		UnloadCurrentLevel();
	}


	void UpdateEngine(double _deltatime, int _updatePhysics)
	{
		//update physics
		if (_updatePhysics)
		{
			physics::UpdateWorld(_deltatime);
		}

		//update actors
		if (current_level_)
		{
			for (const auto& a : current_level_->GetActors())
			{
				a->Tick(_deltatime);
			}
		}

		//HRL rendering//
		HRL_EndFrame();
	}


	/**
	 * Levels
	 */
	void LoadLevel(const char *_levelPath, std::function<void(HGE_Level*)> _onLoaded)
	{
		//std::thread([_levelPath, _onLoaded]()
		//{
			auto* lvl = new HGE_Level();
			lvl->LoadFromFile(_levelPath);
			_onLoaded(lvl);
		//}).detach();
	}

	uint32_t GetEngineHRL_SceneID()
	{
		return hrl_scene_id;
	}


	void OpenLevel(HGE_Level *_level)
	{
		//delete current level before
		if (current_level_)
		{
			delete current_level_;
		}

		current_level_ = _level;
	}

	void UnloadCurrentLevel()
	{
		delete current_level_;
		current_level_ = nullptr;
	}

	HGE_Level* GetCurrentLevel()
	{
		return current_level_;
	}
}
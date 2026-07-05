#include "engine.h"

#include <cassert>

#include "private/engine_backend.h"

#include "actor.h"
#include "level.h"

#include "../filesystem/filesystem.h"
#include "../filesystem/ini_parser.h"

#include "../modules/factory.h"
#include "../std-private/std_module.h"

#include "../physics/world.h"
#include "../physics/private/debug_draw.h"

#include "private/input_manager.h"


#include <vector>
#include <thread>

#include <hrl/hrl.h>



typedef struct {
	//graphics
	HRL_E_APIs backend;

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

//alread declared in actor header
//extern void PlayerControllersTick(double dt);

static void HRLErrorCallback(HRL_EError code, HRL_ESeverity severity, const char *detail)
{
	printf("HRL (rendering error), Error of type : %s, Severity : %s, Details : %s\n", HRL_ErrorEnumToString(code), HRL_SeverityEnumToString(severity), detail);
	if (severity >= HRL_SEVERITY_FATAL)
	{
		exit(code);
	}
}

namespace hge
{
	void InitEngine(uint32_t _mode, const char* _configPath, void* _loader, bool _renderOnScreen)
	{
		gameRunning = true;

		//init le filesystem
		filesystem::InitFilesystem(_mode == HGE_PREVIEW);

		//on utilise pas le filesystem car on utilise toujours un raw file
		filesystem::HGE_Ini configIni(_configPath);

		config.backend = (HRL_E_APIs)configIni.Get<int>("RenderingBackend");
		config.width = configIni.Get<int>("Width");
		config.height = configIni.Get<int>("Height");

		HRL_Init(config.backend);
		printf("window size: %dx%d", config.width, config.height);
		HRL_InitContext(config.width, config.height, _loader);

		HRL_RegisterErrorCallback(HRLErrorCallback);

		hrl_scene_id = HRL_CreateScene(_renderOnScreen);

		gamefactory::InsertFactory(GetStdModule());

		physics::InitPhysics();
		physics::priv::InitDebugDraw();
	}


	int EngineRunning() { return gameRunning; }
	void QuitEngine()
	{
		gameRunning = false;
		UnloadCurrentLevel();
	}


	void UpdateEngine(double _deltatime, int _updateGame)
	{

		//update physics (before update actors)
		if (_updateGame)
		{
			//call player controller tick (internal hidden function)
			//calls process input actor method (called before actor and physics update)
			PlayerControllersTick(_deltatime);

			//update physics, before actor ticks and update
			physics::UpdateWorld(_deltatime);
		}

		if (current_level_)
		{
			for (const auto& a : current_level_->GetActors())
			{
				a->Update(_deltatime);
			}
		}

		if (_updateGame)
		{
			//update actors
			if (current_level_)
			{
				for (const auto& a : current_level_->GetActors())
				{
					a->Tick(_deltatime);
				}
			}

			//reset just pressed keys (called after actors update)
			priv::input::Tick();
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
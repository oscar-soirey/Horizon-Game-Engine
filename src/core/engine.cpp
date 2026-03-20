#include "engine.h"
#include "private/engine_backend.h"

#include "actor.h"
#include "level.h"

#include "../filesystem/filesystem.h"
#include "../filesystem/ini_parser.h"

#include <vector>
#include <thread>

#include <hrl/hrl.h>


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
static std::vector<hge::HGE_Actor*> actors;

static uint32_t hrl_scene_id;

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
	}


	int EngineRunning() { return gameRunning; }
	void QuitEngine()
	{
		gameRunning = false;
		for (const auto& a: actors)
		{
			//le destructeur appelle la libération des autres données
			delete a;
		}
		actors.clear();
	}


	void UpdateEngine(double _deltatime, int _updatePhysics)
	{
		//update actors
		for (const auto& a : actors)
		{
			a->Tick(_deltatime);
		}

		//rendering//
		HRL_EndFrame();
	}


	/**
	 * Actors managing
	 */
	HGE_Actor* SpawnActor(const char *_className)
	{
		return nullptr;
	}


	/**
	 * Levels
	 */
	void LoadLevel(const char *_levelPath, std::function<void(HGE_Level*)> _onLoaded)
	{
		//std::thread([_levelPath, _onLoaded]()
		//{
			auto* level = new HGE_Level();
			level->LoadFromFile(_levelPath);
			_onLoaded(level);
		//}).detach();
	}

	uint32_t GetEngineHRL_SceneID()
	{
		return hrl_scene_id;
	}


	void OpenLevel(HGE_Level *_level)
	{
		//decharger tous les objets current
		for (const auto& a : actors)
		{
			delete a;
		}
		actors.clear();

		actors = _level->GetActors();
	}
}
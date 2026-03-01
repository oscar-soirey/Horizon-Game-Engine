#include "engine.h"
#include "private/engine_backend.h"

#include "actor.h"
#include "level.h"
#include "window.h"
#include "log.h"

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
static std::vector<HGE_Actor*> actors;

static HRL_id engineHRLScene_;

void HGE_InitEngine(uint32_t _mode, const char* _configPath, void* _loader, int _renderOnScreen)
{
	gameRunning = true;

	//init le filesystem
	HGE_filesystem::HGE_InitFilesystem(_mode == HGE_PREVIEW);

	//on utilise pas le filesystem car on utilise toujours un raw file
	HGE_filesystem::HGE_Ini configIni(_configPath);

	config.backend = configIni.Get<int>("RenderingBackend");

	HRL_Init(config.backend);

	HRL_InitContext(config.width, config.height, _loader);

	engineHRLScene_ = HRL_CreateScene(_renderOnScreen);
}


int HGE_EngineRunning() { return gameRunning; }
void HGE_QuitEngine()
{
	gameRunning = false;
	for (const auto& a: actors)
	{
		//le destructeur appelle la libération des autres données
		delete a;
	}
	actors.clear();
}


void HGE_UpdateEngine(double _deltatime, int _updatePhysics)
{
	//update actors
	for (const auto& a : actors)
	{
		a->Tick(_deltatime);
	}

	//rendering//
	HRL_BeginFrame();
	HRL_EndFrame();
}


/**
 * Actors managing
 */
HGE_Actor* HGE_SpawnActor(const char *_className)
{
	return nullptr;
}


/**
 * Levels
 */
void HGE_LoadLevel(const char *_levelPath, std::function<void(HGE_Level*)> _onLoaded)
{
	std::thread([_levelPath, _onLoaded]()
	{
		auto* level = new HGE_Level();
		level->LoadFromFile(_levelPath);
		_onLoaded(level);
	}).detach();
}

void HGE_OpenLevel(HGE_Level *_level)
{
	//decharger tous les objets current
	for (const auto& a : actors)
	{
		delete a;
	}
	actors.clear();

	actors = _level->GetActors();
}




//Engine Backend (private)//
unsigned int HGE_GetEngineHRL_SceneID()
{
	return engineHRLScene_;
}
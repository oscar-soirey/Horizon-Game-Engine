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
#include <cstring>

#include <hrl/hrl.h>

#include <Ogre.h>
#include <OgreLogManager.h>
#include <Compositor/OgreCompositorManager2.h>


namespace
{
	std::unique_ptr<Ogre::Root> _gRoot;
	Ogre::SceneManager* _gSceneManager;
	Ogre::Window* _gWindow = nullptr;
	void* _gWindowHandle;

	Ogre::RenderSystem* TryLoadRenderSystem(const char* pluginName)
	{
		try
		{
			const size_t count = _gRoot->getAvailableRenderers().size();

			_gRoot->loadPlugin(pluginName, true, nullptr);

			const auto& renderers = _gRoot->getAvailableRenderers();

			if(renderers.size() > count)
				return renderers.back();
		}
		catch(const Ogre::Exception&)
		{
		}

		return nullptr;
	}

	Ogre::RenderSystem* AutoAssignRenderSystem()
	{
		const char* plugins[] =
		{
			"RenderSystem_Vulkan",
			"RenderSystem_Direct3D11",
			"RenderSystem_GL3Plus"
	};

		for(const char* plugin : plugins)
		{
			if(Ogre::RenderSystem* rs = TryLoadRenderSystem(plugin))
			{
				_gRoot->setRenderSystem(rs);
				return rs;
			}
		}

		throw std::runtime_error("No supported RenderSystem found.");
	}

	void InitGraphics(const char* renderSystem)
	{
		new Ogre::LogManager();

		// debuggerOutput = false
		// suppressFileOutput = false
		Ogre::LogManager::getSingleton().createLog(
				"Ogre.log",
				true,   // defaultLog
				false,  // debuggerOutput
				false   // suppressFileOutput
		);

		_gRoot = std::make_unique<Ogre::Root>();

		if (std::strcmp(renderSystem, "auto") == 0)
		{
			AutoAssignRenderSystem();
		}
		else
		{
			if(Ogre::RenderSystem* rs = TryLoadRenderSystem(renderSystem))
			{
				_gRoot->setRenderSystem(rs);
			}
			else
			{
				throw std::runtime_error("Specified render system not found");
			}
		}

		_gRoot->initialise(false);

		Ogre::NameValuePairList params;

#ifdef _WIN32
		params["externalWindowHandle"] =
				Ogre::StringConverter::toString(
						reinterpret_cast<size_t>(_gWindowHandle));
#endif

		params["vsync"] = "Yes";

		_gWindow = _gRoot->createRenderWindow(
				"Viewport",
				1280,
				720,
				false,
				&params);

		_gSceneManager = _gRoot->createSceneManager(
			"DefaultSceneManager",
			0
			);

		Ogre::CompositorManager2* compositorManager = _gRoot->getCompositorManager2();
		const Ogre::String workspaceName = "MainWorkspace";

		if (!compositorManager->hasWorkspaceDefinition(workspaceName))
		{
			compositorManager->createBasicWorkspaceDef(workspaceName, Ogre::ColourValue(0.1f, 0.1f, 0.1f));
		}
	}
}


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

		InitGraphics("auto");

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
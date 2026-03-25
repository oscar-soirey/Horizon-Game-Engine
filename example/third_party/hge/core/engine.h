#ifndef HGE_ENGINE_IMPL
#define HGE_ENGINE_IMPL

#include <functional>
#include <cstdint>

#include "build_dll.h"


#define HGE_PREVIEW						0X0000
#define HGE_RELEASE						0X0001

namespace hge
{
	/**
	 * Forward declarations
	 */
	class HGE_Actor;
	class HGE_Level;


	// --- Engine API --- //

	/**
	 * @param _mode Preview = fast graphics, raw files; Release = archive files
	 * @param _configPath path of the config.ini file, always raw file
	 */
	void ENGINE_API InitEngine(uint32_t _mode, const char* _configPath, void* _loader, bool _renderOnScreen);

	/**
	 * @return false if the game should quit
	 */
	int ENGINE_API EngineRunning();
	void ENGINE_API QuitEngine();

	/**
	 * @param _updatePhysics 1 = update physics, 0 = don't update physics, util for editor
	 */
	void ENGINE_API UpdateEngine(double _deltatime, int _updatePhysics);


	// --- Object manage --- //
	/**
	 * @param _className Class name compiled using HGE_Module or class name from C# script class
	 * @return
	 */
	HGE_Actor* ENGINE_API SpawnActor(const char* _className);

	/**
	 * Loads a level asynchronous
	 *  LoadLevelAsync("level1.hge", [](HGE_Level* level)
	 *	{
	 *		std::cout << "level loaded" << std::endl;
	 *	});
	 */
	void ENGINE_API LoadLevel(const char* _levelPath, std::function<void(HGE_Level*)> _onLoaded);

	unsigned int ENGINE_API GetEngineHRL_SceneID();

	void ENGINE_API OpenLevel(HGE_Level* _level);

	HGE_Level* ENGINE_API GetCurrentLevel();
}

#endif
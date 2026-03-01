#ifndef HGE_ENGINE_IMPL
#define HGE_ENGINE_IMPL

#include <functional>
#include <cstdint>


#define HGE_PREVIEW						0X0000
#define HGE_RELEASE						0X0001


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
void HGE_InitEngine(uint32_t _mode, const char* _configPath, void* _loader, int _renderOnScreen = 1);

/**
 * @return false if the game should quit
 */
int HGE_EngineRunning();
void HGE_QuitEngine();

/**
 * @param _updatePhysics 1 = update physics, 0 = don't update physics, util for editor
 */
void HGE_UpdateEngine(double _deltatime, int _updatePhysics);


// --- Object manage --- //
/**
 * @param _className Class name compiled using HGE_Module or class name from C# script class
 * @return
 */
HGE_Actor* HGE_SpawnActor(const char* _className);

/**
 * Loads a level asynchronous
 *  HGE_LoadLevelAsync("level1.hge", [](HGE_Level* level)
 *	{
 *		std::cout << "level loaded" << std::endl;
 *	});
 */
void HGE_LoadLevel(const char* _levelPath, std::function<void(HGE_Level*)> _onLoaded);

void HGE_OpenLevel(HGE_Level* _level);


#endif
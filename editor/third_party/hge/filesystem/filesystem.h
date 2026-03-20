/**
 *
 */

#ifndef HGE_FILESYSTEM
#define HGE_FILESYSTEM

#include <string>
#include "../core/build_dll.h"

namespace hge::filesystem
{
	void ENGINE_API InitFilesystem(bool _useRawFiles);

	std::string ENGINE_API GetFileContent(const char* _path, size_t* _outSize, bool _forceRawFile = false);

}

#endif
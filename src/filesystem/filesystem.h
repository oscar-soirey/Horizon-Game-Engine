/**
 *
 */

#ifndef HGE_FILESYSTEM
#define HGE_FILESYSTEM

#include <string>

namespace hge::filesystem
{
	void InitFilesystem(bool _useRawFiles);

	std::string GetFileContent(const char* _path, size_t* _outSize, bool _forceRawFile = false);

}

#endif
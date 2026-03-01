/**
 *
 */

#ifndef HGE_FILESYSTEM
#define HGE_FILESYSTEM

#include <string>

namespace HGE_filesystem
{
	void HGE_InitFilesystem(bool _useRawFiles);

	std::string HGE_GetFileContent(const char* _path, size_t* _outSize, bool _forceRawFile);

}

#endif
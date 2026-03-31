/**
 *
 */

#ifndef HGE_FILESYSTEM
#define HGE_FILESYSTEM

#include <string>
#include "../core/build_dll.h"

namespace hge::filesystem
{
	/**
	 * 
	 * @param _useRawFiles Use raw file or archive ?
	 */
	void ENGINE_API InitFilesystem(bool _useRawFiles);

	/**
	 * 
	 * @param _path Relative path from package folder or archive
	 * @param _outSize set the variable to file size (in byte)
	 * @param _forceRawFile force to use raw file, usefull for configuration files
	 * @return Content of the file
	 */
	std::string ENGINE_API GetFileContent(const char* _path, size_t* _outSize, bool _forceRawFile = false);

}

#endif
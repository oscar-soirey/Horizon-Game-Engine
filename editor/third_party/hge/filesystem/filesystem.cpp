#include "filesystem.h"

#include <fstream>
#include <iostream>

#include "../core/log.h"


static bool useRawFiles;

namespace HGE_filesystem
{
	void HGE_InitFilesystem(bool _useRawFiles)
	{
		useRawFiles = _useRawFiles;
	}

	std::string HGE_GetFileContent(const char *_path, size_t *_outSize, bool _forceRawFile)
	{
		if (useRawFiles || _forceRawFile)
		{
			std::ifstream file(_path, std::ios::binary | std::ios::ate);
			if (!file)
			{
				LOG_ERROR("Error while openning file " + std::string(_path));
				return nullptr;
			}

			//lit le fichier et stocke la taille
			std::streamsize size = file.tellg();
			//revient au debut du fichier
			file.seekg(0, std::ios::beg);

			std::string content(size, '\0');
			if (!file.read(&content[0], size))
			{
				LOG_ERROR("Error while openning file " + std::string(_path));
				return nullptr;
			}

			*_outSize = (size_t)size;
			return content;
		}
		else
		{
			LOG_ERROR("Fonction pas encore implémentée");
			return nullptr;
		}
	}
}

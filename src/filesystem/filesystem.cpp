#include "filesystem.h"

#include <fstream>
#include <iostream>

#include "../core/log.h"


static bool useRawFiles;

namespace hge::filesystem
{
	void InitFilesystem(bool _useRawFiles)
	{
		useRawFiles = _useRawFiles;
	}

	std::string GetFileContent(const char *_path, size_t *_outSize, bool _forceRawFile)
	{
		if (useRawFiles || _forceRawFile)
		{
			std::ifstream file(_path, std::ios::binary | std::ios::ate);
			if (!file)
			{
				LOG_ERROR("Error while openning file (file doesn't exists) : " + std::string(_path));
				return "";
			}

			//lit le fichier et stocke la taille
			std::streamsize size = file.tellg();
			//revient au debut du fichier
			file.seekg(0, std::ios::beg);

			std::string content(size, '\0');
			if (!file.read(&content[0], size))
			{
				LOG_ERROR("Error while openning file (corrupted file) : " + std::string(_path));
				return "";
			}

			if (_outSize)
			{
				*_outSize = (size_t)size;
			}
			return content;
		}
		else
		{
			LOG_ERROR("Fonction pas encore implémentée");
			return "";
		}
	}
}

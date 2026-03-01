#pragma once

#include <string>

namespace editor
{
	/**
	 * @param _label
	 * @param _defaultDir
	 * @param _filters NULL or {"*.jpg","*.png"}
	 * @param _filterNum Number of filter
	 * @param _fileDescription single description files
	 */
	std::string FileInput(char* buffer, size_t _bufferSize, const char* _label, const char *_defaultDir, int _filterNum = 0, char const * const * const _filters = {}, char const * const _fileDescription = "", const char* _emptyDescription = "");

	//Select directory
	std::string DirectoryInput(char* buffer, size_t _bufferSize, const char* _label, const char* _defaultDir);
}
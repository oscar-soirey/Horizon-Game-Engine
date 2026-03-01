#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace editor
{
	class ContentBrowser;
	void FileButton(const fs::directory_entry& _entry, ContentBrowser* _parent);
}
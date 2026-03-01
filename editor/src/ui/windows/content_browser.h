#pragma once

#include "../window.h"
#include <filesystem>
#include "../../core/history.h"

namespace fs = std::filesystem;

namespace editor
{
	class ContentBrowser : public Window {
	public:
		ContentBrowser();

		fs::path dir_;
		History history_;

	private:
		void content() final;
	};
}
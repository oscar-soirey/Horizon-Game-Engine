#pragma once

#include "../window.h"

namespace editor
{
	class ProjectConfiguration : public Window {
	public:
		ProjectConfiguration();

	private:
		void content() final;

		char iconBuffer[256] = "";
	};
}
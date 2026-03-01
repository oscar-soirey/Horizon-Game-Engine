#pragma once

#include "../window.h"

enum ProjectTemplate {
	Blank
};

namespace editor
{
	class OpenProject : public Window {
	public:
		OpenProject();

	private:
		void content() final;

		ProjectTemplate selected_template_ = Blank;
	};
}
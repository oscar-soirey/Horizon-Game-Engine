#pragma once

#include "../window.h"

namespace editor
{
	class Outliner : public Window {
	public:
		Outliner();

	private:
		void content() final;
	};
}
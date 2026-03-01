#pragma once

#include "../window.h"

#include <hge/modules/factory.h>

namespace editor
{
	class PlaceActors : public Window {
	public:
		PlaceActors();

		factory::Factory project_factory_;

	private:
		void content() final;
	};
}

#pragma once

#include "../window.h"

namespace editor
{
	class ActorDetails : public Window {
	public:
		ActorDetails();

	private:
		void content() final;
	};
}
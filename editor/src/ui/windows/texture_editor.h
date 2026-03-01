#pragma once

#include "../window.h"
#include <filesystem>

#include <hrl/hrl.h>

namespace editor
{
	class TextureEditor : public Window {
	public:
		TextureEditor();

		void SetTexture(HRL_id _textureID);

	private:
		void content() final;

		HRL_id HRL_ID_texture_editing_;
		uint32_t glID_texture_editing_;
	};
}

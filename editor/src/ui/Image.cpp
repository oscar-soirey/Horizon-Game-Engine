#include "Image.h"

#include <hrl/hrl.h>
#include <hrl/hrl_gl.h>
#include <hge/filesystem/filesystem.h>

namespace editor
{
	Image::Image(const char *_path)
	{
		size_t imageSize;
		std::string imageBuffer = HGE_filesystem::HGE_GetFileContent(_path, &imageSize, false);
		HRL_id hrl_id = HRL_CreateTexture(imageBuffer.c_str(), imageSize);
		backend_ID_ = HRL_GL_GetTextureGL_ID(hrl_id);
	}

	uint32_t Image::GetBackendID() const
	{
		return backend_ID_;
	}
}
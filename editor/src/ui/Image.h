#pragma once

#include <cstdint>

namespace editor
{
	class Image {
	public:
		explicit Image(const char* _path);

		uint32_t GetBackendID() const;

	private:
		uint32_t backend_ID_;
	};
}
#pragma once

#include "../window.h"

namespace editor
{
	struct PlotBuffer {
	private:
		float values[128] = {};
		int offset = 0;

	public:
		void Push(float v)
		{
			values[offset] = v;
			offset = (offset+1) % 128;
		}

		float* GetValues()
		{
			return values;
		}

		int GetSize() const
		{
			return 128;
		}

		int GetOffset() const
		{
			return offset;
		}
	};


	class Profiler : public Window {
	public:
		Profiler();

	private:
		void content() final;
	};
}
#include "window.h"

#include <imgui/imgui.h>
#include <hge/core/log.h>

namespace editor
{
	void Window::Show(double _dt)
	{
		if (visible)
		{
			//logic call
			Logic(_dt);

			ImGui::Begin(title, &visible);

			//resize callback
			ImVec2 size = ImGui::GetContentRegionAvail();
			if (size.x != width_ || size.y != height_)
			{
				ResizeCallback((int)size.x, (int)size.y);
				width_ = size.x;
				height_ = size.y;
			}

			content();
			ImGui::End();
		}
	}

	void Window::content()
	{
		LOG_WARNING("Window content is empty");
	}

	void Window::SetTitle(const char *_title)
	{
		title = _title;
	}
}

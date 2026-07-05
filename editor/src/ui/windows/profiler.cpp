#include "profiler.h"

#include "../common.h"
#include <imgui/imgui.h>


#define WIDGET_NUM 4


namespace editor
{
	Profiler::Profiler()
	{
		title = "Profiler";
	}

	void Profiler::content()
	{
		ImGui::PushFont(getFont("std"));

		ImVec2 space = ImGui::GetContentRegionAvail();

		PlotBuffer* frame_buffer = plot_buffers.at("frame_time");
		ImGui::PlotLines(
			"Frame Time",
			frame_buffer->GetValues(),
			frame_buffer->GetSize(),
			frame_buffer->GetOffset(),
			"ms",
			0.f,
			33.f,
			{ space.x, space.y / WIDGET_NUM }
		);


		ImGui::PopFont();
	}
}

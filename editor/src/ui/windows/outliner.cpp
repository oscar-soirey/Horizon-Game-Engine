#include "outliner.h"

#include "../common.h"
#include <imgui/imgui.h>

#include <hge/core/actor.h>


namespace editor
{
  Outliner::Outliner()
  {
    title = "Outliner";
  }

  void Outliner::content()
  {
    ImGui::PushFont(getFont("std"));

    ImVec2 space = ImGui::GetContentRegionAvail();

    ImGui::BeginChild("ScrollBox", space, false);

    for (auto* a : editor::actors_)
    {
      if (a)
      {
        float size_x = ImGui::GetContentRegionAvail().x;

        if (ImGui::Button(a->object_id_.c_str(), ImVec2(size_x, 32.f)))
        {
          editor::selected_actors_.emplace_back(a);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
      }
    }

    ImGui::EndChild();

    ImGui::PopFont();
  }
}

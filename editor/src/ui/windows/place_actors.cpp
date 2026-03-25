#include "place_actors.h"

#include "../common.h"

#include <imgui/imgui.h>

#include "../widgets/ActorTitle.h"
#include "hge/core/actor.h"
#include "hge/core/engine.h"
#include "hge/core/level.h"

namespace editor
{
  PlaceActors::PlaceActors()
  {
    title = "Place Actors";
  }

  void PlaceActors::content()
  {
    ImGui::PushFont(getFont("title"));
    ImGui::Text("Place Actors");
    ImGui::PopFont();

    ImGui::PushFont(getFont("std"));

    for (const auto& [name, constr] : project_factory_)
    {
      //ActorTitle(name.c_str());
      float button_size_x = ImGui::GetContentRegionAvail().x;
      if (ImGui::Button(name.c_str(), ImVec2(button_size_x, 34)))
      {
        auto* act = hge::SpawnActor(name.c_str());

        //name the actor to prevent name colliding
        std::string act_count = std::to_string(hge::GetCurrentLevel()->CountActorsOfClass("Player"));
        act->object_id_ = name + act_count;

        //update actor list for outliner
        editor::actors_ = hge::GetCurrentLevel()->GetActors();
      }
    }

    ImGui::PopFont();
  }
}

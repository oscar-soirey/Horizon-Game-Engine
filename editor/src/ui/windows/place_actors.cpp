#include "place_actors.h"

#include "../common.h"

#include <imgui/imgui.h>

#include "../widgets/ActorTitle.h"

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

    for (const auto& [name, constr] : project_factory_)
    {
      ActorTitle(name.c_str());
    }

    ImGui::PopFont();
  }
}

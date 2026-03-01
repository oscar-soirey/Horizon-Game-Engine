#include "ComboBox.h"

#include "ui/common.h"

#include <imgui/imgui.h>
#include <string>

static int currentItem = 0;

namespace editor
{
	int ComboBox(const char *_label, const char* _items[], int _itemCount)
	{
		ImGui::PushFont(getFont("std"));
		ImGui::Text(_label);
		ImGui::SameLine();

		std::string t = "##" + std::string(_label);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		if (ImGui::BeginCombo(t.c_str(), _items[currentItem]))
		{
			for (int i = 0; i < _itemCount; i++)
			{
				bool selectedCombo = (currentItem == i);

				if (ImGui::Selectable(_items[i], selectedCombo))
					currentItem = i;

				if (selectedCombo)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}
		ImGui::PopFont();
		return currentItem;
	}

}

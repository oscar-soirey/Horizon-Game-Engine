#include "TitleIcon.h"

#include "../Image.h"
#include "../common.h"
#include <imgui/imgui.h>
#include <hge/core/log.h>

#define ICON_SIZE ImVec2(48,48)

namespace editor
{
	void TitleIcon(const char *_title, Image *_image)
	{
		if (!_image)
		{
			LOG_ERROR("TitleIcon, Image : invalid object");
			return;
		}
		ImGui::PushFont(getFont("title"));


		ImGui::BeginGroup();

		//Taille verticale du texte
		float textHeight = ImGui::GetTextLineHeight();

		ImGui::Text(_title);

		ImGui::SameLine();
		float imageHeight = ICON_SIZE.y;

		// Décalage pour centrer l'image par rapport au texte
		float offsetY = (textHeight - imageHeight) * 0.5f;
		if (offsetY < 0.0f) offsetY = 0.0f;

		// Crée un "dummy" vertical pour décaler l'image
		ImGui::Dummy(ImVec2(0, offsetY));
		ImGui::SameLine();

		ImGui::Image(_image->GetBackendID(), ICON_SIZE, ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));

		ImGui::EndGroup();
		ImGui::PopFont();

		//ajouter un espace juste apres le title
		ImGui::Dummy(ImVec2(0, 10));
	}

}
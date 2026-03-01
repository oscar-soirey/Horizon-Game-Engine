#include "texture_editor.h"

#include "../common.h"
#include "../Image.h"

#include <imgui/imgui.h>
#include <hrl/hrl_gl.h>



namespace editor
{
	TextureEditor::TextureEditor()
	{
		title = "Texture Editor";
	}

	void TextureEditor::SetTexture(HRL_id _textureID)
	{
		//on supprime l'ancienne texture via son id hrl
		HRL_DeleteTexture(HRL_ID_texture_editing_);

		//on passe la nouvelle texture id
		HRL_ID_texture_editing_ = _textureID;
		glID_texture_editing_ = HRL_GL_GetTextureGL_ID(_textureID);
	}

	void TextureEditor::content()
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 pos  = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::GetContentRegionAvail();

		ImVec2 end;
		if (size.x > size.y)
		{
			end = ImVec2(
			pos.x + size.y,
			pos.y + size.y
			);
		}
		else
		{
			end = ImVec2(
			pos.x + size.x,
			pos.y + size.x
			);
		}

		//background
		draw->AddImage( GetImage("blank512")->GetBackendID(), pos, end, ImVec2(0.f, 1.f), ImVec2(1.f, 0.f) );

		//image principale
		draw->AddImage(glID_texture_editing_, pos, end, ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
	}
}
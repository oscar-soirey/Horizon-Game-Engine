#include "script_editor.h"

#include "../common.h"

#include <imgui/imgui.h>
#include <imgui_textedit/TextEditor.h>
#include <ostream>
#include <fstream>


namespace editor
{
	ScriptEditor::ScriptEditor()
	{
		title = "Script Editor";

		editor_ = new TextEditor();

		editor_->SetLanguageDefinition(TextEditor::LanguageDefinition::HorizonScript());

		editor_->SetTabSize(2);
		editor_->SetShowWhitespaces(true);
		editor_->SetPalette(TextEditor::GetRetroBluePalette());
	}

	void ScriptEditor::SetContent(const char *_content)
	{
		editor_->SetText(_content);
	}

	void ScriptEditor::content()
	{
		//taille disponible dans la fenetre
		ImVec2 size = ImGui::GetContentRegionAvail();

		ImGui::PushFont(getFont("cascadia-code"));

		editor_->Render("HorizonScript Editor", size);

		ImGui::PopFont();

		//detection du raccourci save : a generaliser a l'editeur plus tard
		auto io = ImGui::GetIO();
		if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_S))
		{
			//save file
			std::ofstream file(editing_path);
			if (!file) return;
			file << editor_->GetText();
		}
	}
}

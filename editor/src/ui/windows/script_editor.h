#pragma once

#include "../window.h"
#include <filesystem>

class TextEditor;

namespace editor
{
	class ScriptEditor : public Window {
	public:
		ScriptEditor();

		void SetContent(const char* _content);

		std::filesystem::path editing_path;

	private:
		void content() final;

		TextEditor* editor_;
	};
}
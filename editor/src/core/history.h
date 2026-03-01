#pragma once

#include <vector>
#include <filesystem>

namespace editor
{
	class History
	{
	public:
		History() = default;

		// Ajoute un nouvel état (navigation normale)
		void Push(const std::filesystem::path& state);

		// Navigation
		bool CanBack() const;
		bool CanForward() const;

		const std::filesystem::path& Back();
		const std::filesystem::path& Forward();

		const std::filesystem::path& Current() const;

		// Utilitaire
		void Clear();
		bool Empty() const;

	private:
		std::vector<std::filesystem::path> states_;
		size_t index_ = 0;
	};
}
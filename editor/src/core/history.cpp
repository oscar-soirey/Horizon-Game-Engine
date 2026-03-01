#include "history.h"

namespace editor
{
	void History::Push(const std::filesystem::path& state)
	{
		// Si on n'est pas à la fin, supprime le futur
		if (!states_.empty() && index_ + 1 < states_.size())
		{
			states_.erase(states_.begin() + index_ + 1, states_.end());
		}

		// Évite les doublons consécutifs
		if (!states_.empty() && states_.back() == state)
			return;

		states_.push_back(state);
		index_ = states_.size() - 1;
	}

	bool History::CanBack() const
	{
		return !states_.empty() && index_ > 0;
	}

	bool History::CanForward() const
	{
		return !states_.empty() && index_ + 1 < states_.size();
	}

	const std::filesystem::path& History::Back()
	{
		if (CanBack())
		{
			index_--;
		}
		return states_[index_];
	}

	const std::filesystem::path& History::Forward()
	{
		if (CanForward())
		{
			index_++;
		}
		return states_[index_];
	}

	const std::filesystem::path& History::Current() const
	{
		if (states_.empty())
			throw std::runtime_error("History is empty");
		return states_[index_];
	}

	void History::Clear()
	{
		states_.clear();
		index_ = 0;
	}

	bool History::Empty() const
	{
		return states_.empty();
	}
}
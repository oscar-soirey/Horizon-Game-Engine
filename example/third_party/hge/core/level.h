//
// Created by User on 28/01/2026.
//

#ifndef LEVEL_H
#define LEVEL_H


#include <vector>
#include "build_dll.h"

namespace hge
{
	class HGE_Actor;

	class ENGINE_API HGE_Level {
	public:
		void LoadFromFile(const char* _path);

		const std::vector<HGE_Actor*>& GetActors() const;

	private:
		std::vector<HGE_Actor*> actors_;
	};
}


#endif //LEVEL_H

//
// Created by User on 28/01/2026.
//

#include "level.h"

#include "log.h"
#include <thread>

void HGE_Level::LoadFromFile(const char *_path)
{
	LOG_INFO("loading level");
	std::this_thread::sleep_for(std::chrono::seconds(3));
	LOG_INFO("level loaded");
}

const std::vector<HGE_Actor *> &HGE_Level::GetActors() const
{
	return actors_;
}
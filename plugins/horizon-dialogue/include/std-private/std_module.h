#pragma once

#include <unordered_map>
#include <string>
#include "../modules/factory.h"

std::unordered_map<std::string, hge::factory::ObjectConstructor> ENGINE_API GetStdModule();
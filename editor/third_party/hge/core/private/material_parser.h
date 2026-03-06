#ifndef HGE_MATERIAL_PARSER_H
#define HGE_MATERIAL_PARSER_H

#include <hrl/hrl.h>

namespace hge::priv
{
	HRL_id CreateMaterialFromJson(const char* _path);
}

#endif
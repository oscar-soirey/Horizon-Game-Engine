#include "common.h"

static uint32_t current_id_ = 0;
uint32_t Generate_HGE_ID()
{
	return current_id_++;
}

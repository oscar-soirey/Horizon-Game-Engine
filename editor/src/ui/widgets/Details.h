#pragma once

#include <string>
#include <hge/core/common.h>

namespace editor
{
	/**
	 * Shows an int input bound to `ref`. Updates `ref` on Enter.
	 * @return true if Enter was pressed this frame, false otherwise.
	 */
	bool DetailInt(const char* label, int& ref);
	bool DetailFloat(const char* label, float& ref);
	bool DetailBool(const char* label, bool& ref);
	bool DetailString(const char* label, std::string& ref);
	bool DetailVec2(const char* label, HGE_Vec2& ref);
	bool DetailVec3(const char* label, HGE_Vec3& ref);
	bool DetailVec4(const char* label, HGE_Vec4& ref);
	bool DetailTransform(const char* label, HGE_Transform& ref);
}
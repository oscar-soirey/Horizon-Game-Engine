#include "material_parser.h"

#include "runtime_ressources.h"
#include "../../filesystem/filesystem.h"

#include <nlohmann/json.hpp>
#include <filesystem>

#include "../log.h"

namespace hge::priv
{
	HRL_id CreateMaterialFromJson(const char* _path)
	{
		std::filesystem::path matPath = _path;

		std::string fileData = filesystem::GetFileContent(_path, nullptr, true);
		nlohmann::json jfile = nlohmann::json::parse(fileData);
		if (!jfile.contains("surface") && !jfile.contains("shader"))
		{
			LOG_ERROR("HRL_CreateMaterialFromJson : file doesn't contains at least 'surface' and 'shader' key");
			return HRL_InvalidID;
		}

		HRL_id matID = HRL_CreateMaterial(HRL_SpriteShader);
		for (const auto& [key, value] : jfile["surface"].items())
		{
			std::string uniform = "T_" + key;
			std::filesystem::path texRelPath = value.get<std::string>();
			std::filesystem::path texAbsPath = matPath.parent_path() / texRelPath;
			std::string texAbsStr = texAbsPath.string();
			HRL_MaterialSetTexture(matID, uniform.c_str(), runtime_ressources::AddTexture(texAbsStr.c_str()));
		}
		return matID;
	}
}
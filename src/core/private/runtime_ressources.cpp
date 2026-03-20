#include "runtime_ressources.h"

#include "filesystem/filesystem.h"
#include "material_parser.h"

#include <unordered_map>
#include <string>

namespace
{
	std::unordered_map<std::string, HRL_id> textures_;
	std::unordered_map<std::string, HRL_id> materials_;
}

namespace hge::priv::runtime_ressources
{
	HRL_id AddTexture(const char *_path)
	{
		HRL_id tex = HRL_InvalidID;

		//on cherche la texture dans la map
		auto it = textures_.find(_path);
		if (it == textures_.end())
		{
			//on ne trouve pas la texture dans la map,
			//on crée alors la texture HRL et on l'ajoute a la map

			size_t texSize;
			std::string texData = filesystem::GetFileContent(_path, &texSize);

			tex = HRL_CreateTexture(texData.c_str(), texSize);
			printf("create texture, path : %s, id : %u\n", _path, tex);

			textures_.emplace(_path, tex);

			return tex;
		}
		return it->second;
	}

	HRL_id AddMaterial(const char *_path)
	{
		HRL_id mat = HRL_InvalidID;

		//on cherche la texture dans la map
		auto it = materials_.find(_path);
		if (it == materials_.end())
		{
			//on ne trouve pas le material dans la map,
			//on crée alors le material HRL et on l'ajoute a la map

			mat = CreateMaterialFromJson(_path);

			materials_.emplace(_path, mat);

			return mat;
		}
		return it->second;
	}

}
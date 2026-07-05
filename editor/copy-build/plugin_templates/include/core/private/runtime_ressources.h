/**
 * Ce fichier sert à gérer les objets runtime du moteur comme les textures, les materials, etc...
 */
#ifndef HGE_ASSETS_MANAGER_H
#define HGE_ASSETS_MANAGER_H

#include <hrl/hrl.h>


namespace hge::priv::runtime_ressources
{
	/**
	 * Protégé contre les copies
	 */
	HRL_id AddTexture(const char* _path);
	HRL_id GetTextureID(const char* _path);

	/**
	 * Protégé des copies
	 */
	HRL_id AddMaterial(const char* _path);
	HRL_id GetMaterialID(const char* _path);
}

#endif
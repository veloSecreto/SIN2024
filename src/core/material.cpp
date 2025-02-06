#include "material.hpp"

#include "../api/opengl/types/textureGenerator.h"
#include "../core/asset_manager.h"

void Material::setParameter(const TextureType& type, float r, float g, float b)
{
	uint32_t texID = generateColorTexture(r, g, b);

	switch (type) {
		case TextureType::ALBEDO:
			albedo.handle = texID;
			break;

		case TextureType::ROUGHNESS:
			roughness.handle = texID;
			break;

		case TextureType::METALLIC:
			metallic.handle = texID;
			break;

		case TextureType::AO:
			ao.handle = texID;
			break;
		default:
			std::cout << "Invalid texture type, couldn't set parameter for material instance" << std::endl;
			break;
	}
}


void Material::setParameter(const TextureType& type, const glm::vec3& color)
{
	setParameter(type, color.x, color.y, color.z);
}

void Material::setParameter(const TextureType& type, const std::string& name)
{
	uint32_t texID = AssetManager::getTextureByName(name).handle;

	switch (type) {
		case TextureType::ALBEDO:
			albedo.handle = texID;
			break;

		case TextureType::ROUGHNESS:
			roughness.handle = texID;
			break;

		case TextureType::METALLIC:
			metallic.handle = texID;
			break;

		case TextureType::AO:
			ao.handle = texID;
			break;
		default:
			std::cout << "Invalid texture type, couldn't set parameter for material instance" << std::endl;
			break;
	}
}
#pragma once

#include "texture.hpp"
#include <glm/glm.hpp>


struct Material {
	Texture albedo;
	Texture roughness;
	Texture metallic;
	Texture ao;

	Material() = default;
	void setParameter(const TextureType& type, float r, float g, float b);
	void setParameter(const TextureType& type, const glm::vec3& color);
	void setParameter(const TextureType& type, const std::string& name);
};
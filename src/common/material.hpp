#pragma once

#include "rendererCommon.h"

struct Material {
	Texture albedo;
	Texture roughness;
	Texture metallic;
	Texture ao;

	Material() = default;
};
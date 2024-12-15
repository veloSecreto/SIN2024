#pragma once

#include <iostream>

// definations here
#define BG_COLOR 0.2f, 0.2f, 0.2f
#define FAR_PLANE 100.0f
#define NEAR_PLANE 0.01f
#define FOVY 50.0f

// constantss here
const std::string ROOT_DIR = "../../";

// enums here
enum class API { UNDEFINED, OPENGL, VULKAN };
enum class WindowMode { WINDOWED, FULLSCREEN };
enum class TextureType { DIFFUSE, ROUGHNESS, METALLIC, AO, EMISSIVE };
enum class LightType { POINT, FLASH };
enum class RenderMode { FORWARD, DEFERRED };
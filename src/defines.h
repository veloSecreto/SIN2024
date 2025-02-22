#pragma once

#include <iostream>

// definations here
#define BG_COLOR 0.0f, 0.0f, 0.0f
#define FAR_PLANE 100.0f
#define NEAR_PLANE 0.01f
#define FOVY 50.0f
#define SIN_PI 3.14159265359

// constantss here
const std::string ROOT_DIR = "../../";
const int SHADOW_MAP_WIDTH = 1024;
const int SHADOW_MAP_HEIGHT = 1024;

// enums here
enum class API { UNDEFINED, OPENGL, VULKAN };
enum class Mode { Editing, Playing };
enum class WindowMode { WINDOWED, FULLSCREEN };
enum class TextureType { ALBEDO, ROUGHNESS, METALLIC, AO, EMISSIVE };
enum class LightType { POINT, FLASH };
enum class RenderMode { FORWARD, DEFERRED };
enum class DebugMode { AABB, NONE };
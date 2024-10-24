#pragma once

#pragma warning(push, 0)
#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
<<<<<<< HEAD
#include "glm/gtx/hash.hpp"
=======
#include <glm/gtx/hash.hpp>
#include <glm/gtx/string_cast.hpp>
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
#pragma warning(pop)

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
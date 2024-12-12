#pragma once

#include <glad/glad.h>
#include <iostream>

struct Skybox {
	private:
		uint32_t ID;

	public:
		Skybox() = default;
		Skybox(const std::string& path, std::string format);
		void render();
		uint32_t& getID();
};
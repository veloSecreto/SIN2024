#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace Math {
	inline glm::vec3 min(const glm::vec3& vecA, const glm::vec3& vecB) {
		return glm::vec3(std::min(vecA.x, vecB.x), std::min(vecA.y, vecB.y), std::min(vecA.z, vecB.z));
	}

	inline glm::vec3 max(const glm::vec3& vecA, const glm::vec3& vecB) {
		return glm::vec3(std::max(vecA.x, vecB.x), std::max(vecA.y, vecB.y), std::max(vecA.z, vecB.z));
	}
};
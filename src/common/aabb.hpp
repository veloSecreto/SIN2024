#pragma once

#include <glm/glm.hpp>

struct AABB {
	glm::vec3 min;
	glm::vec3 max;

	AABB() : min(std::numeric_limits<float>::max()), max(-std::numeric_limits<float>::max()) {}
	AABB(const glm::vec3& minBounds, const glm::vec3& maxBounds) {
		min = minBounds;
		max = maxBounds;
	}
};
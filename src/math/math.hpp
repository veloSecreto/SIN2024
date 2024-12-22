#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "../common/rendererCommon.h"
#include "../common/aabb.hpp"
#include "../common/types.h"

namespace Math {
	inline glm::vec3 min(const glm::vec3& vecA, const glm::vec3& vecB) {
		return glm::vec3(std::min(vecA.x, vecB.x), std::min(vecA.y, vecB.y), std::min(vecA.z, vecB.z));
	}

	inline glm::vec3 max(const glm::vec3& vecA, const glm::vec3& vecB) {
		return glm::vec3(std::max(vecA.x, vecB.x), std::max(vecA.y, vecB.y), std::max(vecA.z, vecB.z));
	}

	inline AABB calculateAABB(const std::vector<Vertex>& vertices) {
		AABB aabb;

		for (unsigned int i = 0; i < vertices.size(); ++i) {
			aabb.min = min(vertices[i].position, aabb.min);
			aabb.max = max(vertices[i].position, aabb.max);
		}

		return aabb;
	}

	inline AABB calculateAABB(AABB aabb, const std::vector<Vertex>& vertices) {
		for (unsigned int i = 0; i < vertices.size(); ++i) {
			aabb.min = min(vertices[i].position, aabb.min);
			aabb.max = max(vertices[i].position, aabb.max);
		}

		return aabb;
	}

	inline AABB calculateOBB(AABB aabb, const Transform& transform) {
		glm::vec3 obbCenter = (aabb.min + aabb.max) * 0.5f;
		glm::vec3 obbExtent = (aabb.max - aabb.min) * 0.5f;
		const auto& m_model = transform.to_mat4();
		glm::vec3 right = glm::vec3(m_model[0]);
		glm::vec3 up = glm::vec3(m_model[1]);
		glm::vec3 forward = glm::vec3(m_model[2]);
		glm::vec3 worldCenter = glm::vec3(m_model * glm::vec4(obbCenter, 1.0f));
		glm::vec3 worldExtent = glm::abs(obbExtent.x * right) + glm::abs(obbExtent.y * up) + glm::abs(obbExtent.z * forward);
		aabb.min = worldCenter - worldExtent;
		aabb.max = worldCenter + worldExtent;
		return aabb;
	}
};
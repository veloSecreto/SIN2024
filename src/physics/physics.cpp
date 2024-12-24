#include "physics.h"
#include "../math/math.hpp"

namespace Physics {

	AABB calculateAABB(const std::vector<Vertex>& vertices) {
		AABB aabb;

		for (unsigned int i = 0; i < vertices.size(); ++i) {
			aabb.min = Math::min(vertices[i].position, aabb.min);
			aabb.max = Math::max(vertices[i].position, aabb.max);
		}

		return aabb;
	}

	AABB calculateAABB(AABB aabb, const std::vector<Vertex>& vertices) {
		for (unsigned int i = 0; i < vertices.size(); ++i) {
			aabb.min = Math::min(vertices[i].position, aabb.min);
			aabb.max = Math::max(vertices[i].position, aabb.max);
		}

		return aabb;
	}

	AABB calculateOBB(AABB aabb, Transform& transform) {
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

	bool intersection(const Ray& ray, const AABB& aabb) {
		float t1 = (aabb.min.x - ray.origin.x) / ray.direction.x;
		float t2 = (aabb.max.x - ray.origin.x) / ray.direction.x;
		float t3 = (aabb.min.y - ray.origin.y) / ray.direction.y;
		float t4 = (aabb.max.y - ray.origin.y) / ray.direction.y;
		float t5 = (aabb.min.z - ray.origin.z) / ray.direction.z;
		float t6 = (aabb.max.z - ray.origin.z) / ray.direction.z;

		float tMinX = glm::min(t1, t2);
		float tMaxX = glm::max(t1, t2);
		float tMinY = glm::min(t3, t4);
		float tMaxY = glm::max(t3, t4);
		float tMinZ = glm::min(t5, t6);
		float tMaxZ = glm::max(t5, t6);

		float tNear = glm::max(glm::max(tMinX, tMinY), tMinZ);
		float tFar = glm::min(glm::min(tMaxX, tMaxY), tMaxZ);

		if (tNear > tFar || tFar < 0.0f) {
			return false;
		}

		return true;
	}

	bool intersection(const Ray& ray, const AABB& aabb, float& distance) {
		float t1 = (aabb.min.x - ray.origin.x) / ray.direction.x;
		float t2 = (aabb.max.x - ray.origin.x) / ray.direction.x;
		float t3 = (aabb.min.y - ray.origin.y) / ray.direction.y;
		float t4 = (aabb.max.y - ray.origin.y) / ray.direction.y;
		float t5 = (aabb.min.z - ray.origin.z) / ray.direction.z;
		float t6 = (aabb.max.z - ray.origin.z) / ray.direction.z;

		float tMinX = glm::min(t1, t2);
		float tMaxX = glm::max(t1, t2);
		float tMinY = glm::min(t3, t4);
		float tMaxY = glm::max(t3, t4);
		float tMinZ = glm::min(t5, t6);
		float tMaxZ = glm::max(t5, t6);

		float tNear = glm::max(glm::max(tMinX, tMinY), tMinZ);
		float tFar = glm::min(glm::min(tMaxX, tMaxY), tMaxZ);

		if (tNear > tFar || tFar < 0.0f) {
			return false;
		}

		glm::vec3 intersectionPoint = ray.origin + tNear * ray.direction;
		distance = glm::length(intersectionPoint - ray.origin);
		return true;
	}
}
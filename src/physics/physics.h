#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "ray.hpp"
#include "transform.hpp"
#include "aabb.hpp"
#include "../core/vertex.hpp"

namespace Physics {
	AABB calculateAABB(const std::vector<Vertex>& vertices);
	AABB calculateAABB(AABB aabb, const std::vector<Vertex>& vertices);
	AABB calculateOBB(AABB aabb, Transform& transform);
	bool intersection(const Ray& ray, const AABB& aabb);
	bool intersection(const Ray& ray, const AABB& aabb, float& distance);
};
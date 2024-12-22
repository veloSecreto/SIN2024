#include "common.h"

namespace Util {
    // Converts a 3 component vector to string including a new line
    inline std::string debug(const glm::vec3& vector) {
        return std::to_string(vector.x) + " " + std::to_string(vector.y) + " " + std::to_string(vector.z) + "\n";
    }
};
#pragma once

#include <glm/glm.hpp>

struct InstanceData {
    glm::mat4 m_model;
    int albedoIndex;
    int roughnessIndex;
    int metallicIndex;
    int aoIndex;
};
#pragma once

#include "glm/glm.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    struct Light {
    public:
        glm::vec3 ambient  = glm::vec3(0.05f, 0.05f, 0.05f);
        glm::vec3 diffuse  = glm::vec3(0.4f, 0.4f, 0.4f);
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    };
}
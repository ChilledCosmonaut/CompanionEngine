#pragma once

#include "glm/glm.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    struct Light {
    public:
        glm::vec3 ambient{};
        glm::vec3 diffuse{};
        glm::vec3 specular{};
    };
}
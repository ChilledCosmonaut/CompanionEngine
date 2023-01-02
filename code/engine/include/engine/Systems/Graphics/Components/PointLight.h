#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    struct PointLight : Light {
    public:
        glm::vec3 constant{};
        glm::vec3 linear{};
        glm::vec3 quadratic{};
    };
}

#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    struct DirectionLight : Light {
    public:
        glm::vec3 direction{};
    };
}
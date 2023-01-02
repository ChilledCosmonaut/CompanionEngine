#pragma once

#include "glm/glm.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    struct DirectionLight {
    public:
        glm::vec3 direction{};
    };
}
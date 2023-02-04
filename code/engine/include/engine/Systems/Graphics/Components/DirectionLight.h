#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    /**
     * Component for directional light.
     * Used as a identifier component for the render system.
     */
    struct DirectionLight : Light {
    public:
        /// Determines the direction towards which the light points.
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
    };
}
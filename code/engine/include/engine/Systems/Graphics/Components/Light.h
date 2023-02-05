#pragma once

#include "glm/glm.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    /**
     * Parent class for all light variations.
     */
    struct Light {
    public:
        /// Ambient spectrum for emitted light
        glm::vec3 ambient  = glm::vec3(0.05f, 0.05f, 0.05f);
        /// Diffuse spectrum for emitted light
        glm::vec3 diffuse  = glm::vec3(0.4f, 0.4f, 0.4f);
        /// Specular spectrum for emitted light
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    };
}
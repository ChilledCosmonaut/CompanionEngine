#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    struct SpotLight : Light {
    public:
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

        float constant      = 1.0f;
        float linear        = 0.09f;
        float quadratic     = 0.032f;

        float cutoff        = glm::cos(glm::radians(12.5f));
        float outerCutoff   = glm::cos(glm::radians(15.0f));
    };
}
#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    struct SpotLight : Light {
    public:
        glm::vec3 direction{};

        float constant{};
        float linear{};
        float quadratic{};

        float cutoff{};
        float outerCutoff{};
    };
}
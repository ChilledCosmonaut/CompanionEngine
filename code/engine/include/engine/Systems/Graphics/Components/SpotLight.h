#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace gl3::engine::Graphics {

    /**
     * Component for spot light.
     * Used as a identifier component for the render system.
     */
    struct SpotLight : Light {
    public:
        /// Determines the direction towards which the light points.
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

        /// Constant drop off factor for light attenuation. **Should be kept at 1.0f**
        float constant  = 1.0f;
        /// Linear drop off factor for light attenuation.
        float linear    = 0.09f;
        /// Quadratic drop off factor for light attenuation.
        float quadratic = 0.032f;

        /// Inner light cut off angle. Light starts to slowly fade.
        float cutoff        = glm::cos(glm::radians(12.5f));
        /// Outer light cut off angle. Provides a hard limit on how wide the light will be.
        float outerCutoff   = glm::cos(glm::radians(15.0f));
    };
}
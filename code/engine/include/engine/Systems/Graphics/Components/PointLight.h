#pragma once

#include "Light.h"

namespace gl3::engine::Graphics {

    /**
     * Component for point light.
     * Used as a identifier component for the render system.
     */
    struct PointLight : Light {
    public:
        /// Constant drop off factor for light attenuation. **Should be kept at 1.0f**
        float constant  = 1.0f;
        /// Linear drop off factor for light attenuation.
        float linear    = 0.09f;
        /// Quadratic drop off factor for light attenuation.
        float quadratic = 0.032f;
    };
}

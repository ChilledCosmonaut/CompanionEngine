#pragma once

#include "Light.h"

namespace gl3::engine::Graphics {

    struct PointLight : Light {
    public:
        float constant  = 1.0f;
        float linear    = 0.09f;
        float quadratic = 0.032f;
    };
}

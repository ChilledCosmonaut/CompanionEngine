#pragma once

#include "Light.h"

namespace gl3::engine::Graphics {

    struct PointLight : Light {
    public:
        float constant{};
        float linear{};
        float quadratic{};
    };
}

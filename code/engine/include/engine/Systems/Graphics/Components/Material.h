#pragma once

#include "engine/Systems/Graphics/mesh.h"

namespace gl3::engine::Graphics {

    struct Material {

    public:
        Texture ambient;
        Texture diffuse;
        Texture specular;
        Texture normal;
        float shininess;
    };
}
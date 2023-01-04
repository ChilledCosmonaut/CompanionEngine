#pragma once

namespace gl3::engine::Graphics {

    struct Texture {
        unsigned int id;
        assets::Images name;
    };

    struct Material {

    public:
        std::shared_ptr<Texture> ambient;
        std::shared_ptr<Texture> diffuse;
        std::shared_ptr<Texture> specular;
        std::shared_ptr<Texture> normal;
        float shininess;
    };
}
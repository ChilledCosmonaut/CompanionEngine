#pragma once

namespace gl3::engine::Graphics {

    struct Texture {
        unsigned int id;
        assets::Images name;
    };

    /// Material component
    struct Material {
    public:
        /// Ambient texture for rendering
        std::shared_ptr<Texture> ambient;
        /// Diffuse texture for rendering
        std::shared_ptr<Texture> diffuse;
        /// Specular texture for rendering
        std::shared_ptr<Texture> specular;
        /// Normal texture for rendering
        std::shared_ptr<Texture> normal;
        /// Shininess factor for rendering
        float shininess = 32.0f;
    };
}
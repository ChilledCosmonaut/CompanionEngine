#pragma once

#include "engine/Systems/Graphics/shader.h"
#include <string>
#include <Assets.h>

namespace gl3::engine::Graphics {
    /**
     * Component for sprite rendering.
     * Allows to render a specific image.
     */
    struct UI {
    public:
        UI() {
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$UIVertexShader$glsl, assets::shaders$UIFragmentShader$glsl);
        };

        /// Asset image id
        assets::Images imageName;
        std::shared_ptr<Graphics::Texture> image;
        /// Size image should take up
        glm::vec2 dimensions = glm::vec2(100, 100);
        std::shared_ptr<Graphics::shader> shader = nullptr;
        unsigned int VAO, VBO;
    };
}
#pragma once

#include "engine/Systems/Graphics/shader.h"
#include <string>
#include <Assets.h>

namespace gl3::engine::Graphics {
    struct UI {
    public:
        UI() {
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$TextVertexShader$glsl, assets::shaders$TextFragmentShader$glsl);
        };

        assets::Images imageName;
        std::shared_ptr<Graphics::Texture> image;
        glm::vec2 dimensions = glm::vec2(100, 100);
        std::shared_ptr<Graphics::shader> shader = nullptr;
        unsigned int VAO, VBO;
    };
}
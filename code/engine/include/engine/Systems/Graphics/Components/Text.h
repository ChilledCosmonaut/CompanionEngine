#pragma once

#include "engine/Systems/Graphics/shader.h"
#include <string>
#include "../../../../../src/Systems/FileManager/FontLoader.h"

namespace gl3::engine::Graphics {
    struct Text {
    public:
        Text() {
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$TextVertexShader$glsl, assets::shaders$TextFragmentShader$glsl);
        };

        std::string content;
        std::string fontName;
        std::shared_ptr<std::map<GLchar, filesystem::Character>> font;
        unsigned int fontSize;
        glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
        std::shared_ptr<Graphics::shader> shader = nullptr;
        unsigned int VAO, VBO;
    };
}
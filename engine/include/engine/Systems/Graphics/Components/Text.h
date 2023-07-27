#pragma once

#include "engine/Systems/Graphics/shader.h"
#include <string>
#include "../../../../../src/Systems/FileManager/FontLoader.h"
#include <Assets.h>

namespace gl3::engine::Graphics {
    /**
     * Component for text rendering.
     * Allows to render a string of text by specifying font and other properties.
     */
    struct Text {
    public:
        Text() {
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$TextVertexShader$glsl, assets::shaders$TextFragmentShader$glsl);
        };

        /// String to be rendered
        std::string content;
        /// Asset id of requested font
        assets::Fonts fontName = assets::Fonts::fonts$RobotoRegular$ttf;
        std::shared_ptr<std::map<GLchar, filesystem::Character>> font;
        /// Font size
        unsigned int fontSize = 14;
        /// Font color
        glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
        std::shared_ptr<Graphics::shader> shader = nullptr;
        unsigned int VAO, VBO;
    };
}
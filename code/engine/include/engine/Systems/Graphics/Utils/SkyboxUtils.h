#pragma once

#include "engine/Scene.h"
#include "engine/Systems/Graphics/Components/Skybox.h"

namespace gl3::engine::Graphics::Utils {

    class SkyboxUtils {



    public:

        void SetVAO(Components::SkyboxComponent &skybox, GLuint vao) {
            skybox.VAO = vao;
        }

        void SetVBO(Components::SkyboxComponent &skybox, GLuint vbo) {
            skybox.VBO = vbo;
        }

        void SetTexture(Components::SkyboxComponent &skybox, GLuint newTexture) {
            skybox.texture = newTexture;
        }
    };
}
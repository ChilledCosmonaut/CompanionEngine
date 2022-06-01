#pragma once

#include "engine/EntityComponentSystem/Component.h"
#include "engine/GraphicsEngine/shader.h"

namespace gl3::engine::Graphics::Components {
class SkyboxComponent : public gl3::engine::entityComponentSystem::Component {
    public:
        SkyboxComponent(const std::string& name, const std::string& texture_path);

        void SetVAO(GLuint vao) {
            VAO = vao;
        }

        void SetVBO(GLuint vbo) {
            VBO = vbo;
        }

        void SetTexture(GLuint newTexture) {
            this->texture = newTexture;
        }

        ~SkyboxComponent();

    private:
        Graphics::shader shader  = Graphics::shader("shaders/SkyBoxVertexShader.glsl", "shaders/SkyBoxFragmentShader.glsl");
        unsigned int VAO, VBO;
        std::vector<std::string> faces{
                "AllSky_Space_AnotherPlanet_Cam_3_Right-X.png",
                "AllSky_Space_AnotherPlanet_Cam_2_Left+X.png",
                "AllSky_Space_AnotherPlanet_Cam_4_Up+Y.png",
                "AllSky_Space_AnotherPlanet_Cam_5_Down-Y.png",
                "AllSky_Space_AnotherPlanet_Cam_0_Front+Z.png",
                "AllSky_Space_AnotherPlanet_Cam_1_Back-Z.png"
        };
        unsigned int texture;
        float vertices[108] = {
                // positions
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f,  1.0f
        };
    };
}

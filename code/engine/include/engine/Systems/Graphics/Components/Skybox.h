#pragma once

#include "engine/Systems/Graphics/shader.h"

namespace gl3::engine::Graphics {
    struct Skybox {

    public:
        Skybox() {
            shader = std::make_shared<Graphics::shader>
                    ("shaders/SkyBoxVertexShader.glsl", "shaders/SkyBoxFragmentShader.glsl");
        };
        Skybox(const Skybox&) = default;
        Skybox(int VAO, int VBO, int texture) : VAO(VAO), VBO(VBO), texture(texture) {
            shader = std::make_shared<Graphics::shader>
                    ("shaders/SkyBoxVertexShader.glsl", "shaders/SkyBoxFragmentShader.glsl");
        }

        float vertices[108]= {
                // positions
                -1.0f, 1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,

                -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,

                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,

                -1.0f, 1.0f, -1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, 1.0f
        };

        std::shared_ptr<Graphics::shader> shader = nullptr;
        unsigned int VAO, VBO, texture;
        std::vector<std::string> faces{
                "AllSky_Space_AnotherPlanet_Cam_3_Right-X.png",
                "AllSky_Space_AnotherPlanet_Cam_2_Left+X.png",
                "AllSky_Space_AnotherPlanet_Cam_4_Up+Y.png",
                "AllSky_Space_AnotherPlanet_Cam_5_Down-Y.png",
                "AllSky_Space_AnotherPlanet_Cam_0_Front+Z.png",
                "AllSky_Space_AnotherPlanet_Cam_1_Back-Z.png"
        };
    };
}

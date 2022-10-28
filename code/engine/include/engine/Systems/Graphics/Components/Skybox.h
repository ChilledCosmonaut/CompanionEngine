#pragma once

#include "engine/Systems/Graphics/shader.h"
#include "engine/Systems/FileManager/Test.h"

namespace gl3::engine::Graphics {
    struct Skybox {

    public:
        Skybox() {
            shader = std::make_shared<Graphics::shader>
                    (assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);
        };
        Skybox(const Skybox&) = default;
        Skybox(int VAO, int VBO, int texture) : VAO(VAO), VBO(VBO), texture(texture) {
            shader = std::make_shared<Graphics::shader>
                    (assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);
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
                "AllSky_Space_AnotherPlanet_Cam_3_Right_minusX.png",
                "AllSky_Space_AnotherPlanet_Cam_2_Left_plusX.png",
                "AllSky_Space_AnotherPlanet_Cam_4_Up_plusY.png",
                "AllSky_Space_AnotherPlanet_Cam_5_Down_minusY.png",
                "AllSky_Space_AnotherPlanet_Cam_0_Front_plusZ.png",
                "AllSky_Space_AnotherPlanet_Cam_1_Back_minusZ.png"
        };
    };
}

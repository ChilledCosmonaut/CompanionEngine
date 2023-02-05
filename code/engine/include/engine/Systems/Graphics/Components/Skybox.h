#pragma once

#include "engine/Systems/Graphics/shader.h"
#include "generated/Assets.h"
#include "engine/Systems/FileManager/FileManager.h"

namespace gl3::engine::Graphics {

    /**
     * Skybox Component.
     * Currently only supports one specific skybox.
     */
    struct Skybox {
    public:
        Skybox() {/*
            shader = std::make_shared<Graphics::shader>
                    (assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);*/
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);
        };
        Skybox(const Skybox&) = default;
        Skybox(int VAO, int VBO, int texture) : VAO(VAO), VBO(VBO), texture(texture) {
            /*shader = std::make_shared<Graphics::shader>
                    (assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);*/
            shader = filesystem::FileManager::GetFileManager()->getAsset(assets::shaders$SkyBoxVertexShader$glsl, assets::shaders$SkyBoxFragmentShader$glsl);
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
        std::vector<assets::Images> faces{
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_3_Right_minusX$png,
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_2_Left_plusX$png,
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_4_Up_plusY$png,
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_5_Down_minusY$png,
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_0_Front_plusZ$png,
                assets::Images::textures$SpaceSkybox$AllSky_Space_AnotherPlanet_Cam_1_Back_minusZ$png
        };
    };
}

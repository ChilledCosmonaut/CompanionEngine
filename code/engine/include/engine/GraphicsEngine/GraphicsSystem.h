#pragma once

#include <iostream>

#include "Model.h"
#include "camera.h"
#include "Transform.h"

#include "engine/EntityComponentSystem/System.h"

#include "engine/FileManager/FileManager.h"

namespace gl3::engine::Graphics{

    struct Skybox{
        Graphics::shader shader  = Graphics::shader("shaders/SkyBoxVertexShader.glsl", "shaders/SkyBoxFragmentShader.glsl");
        unsigned int VAO, VBO;
        vector<std::string> faces{
                "AllSky_Space_AnotherPlanet_Cam_3_Right-X.png",
                "AllSky_Space_AnotherPlanet_Cam_2_Left+X.png",
                "AllSky_Space_AnotherPlanet_Cam_4_Up+Y.png",
                "AllSky_Space_AnotherPlanet_Cam_5_Down-Y.png",
                "AllSky_Space_AnotherPlanet_Cam_0_Front+Z.png",
                "AllSky_Space_AnotherPlanet_Cam_1_Back-Z.png"
        };
        unsigned int texture;
        float vertices[];
    };

    class GraphicsSystem : entityComponentSystem::System {
    public:
        GraphicsSystem() = default;

        void Render();

        void Start(Game &game) {
            SetUpSkybox();
        }

        void Update(Game &game);

        void OnShutdown(Game &engine);

        [[maybe_unused]] [[nodiscard]] const glm::vec3 &getDirectionalLightPositionAtIndex(int index) const;

        [[maybe_unused]] void setDirectionalLightPosition(glm::vec3 &directionalLightPosition);

        [[maybe_unused]] [[nodiscard]] const std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>> &getSceneModelAtIndex(int index) const;

        [[maybe_unused]] void AddSceneModels(const Model& model, const Graphics::shader* shader, Graphics::Transform* modelMatrix);

    private:
        void SetUpSkybox();
        void DisplaySkybox();
        void DisplayLights();
        void DisplayModels();

        vector<std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>>> sceneModels;
        Camera camera;
    public:
        [[nodiscard]] Camera *getCamera();

    private:
        vector<glm::vec3> directionalLightPositions;
        Skybox skybox;
    };
}
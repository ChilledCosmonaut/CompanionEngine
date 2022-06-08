#pragma once

#include <iostream>

#include "engine/GraphicsEngine/Model.h"
#include "engine/GraphicsEngine/camera.h"
#include "engine/GraphicsEngine/Transform.h"

#include "engine/FileManager/FileManager.h"
#include "SkyboxRenderer.h"

namespace gl3::engine::Graphics::Systems{

    class GraphicsSystem {
    public:
        void Start(Scene &scene) {
            skyboxRenderer.SetupSkybox(scene);
        }

        void Render(Scene &scene);

        /*void Update(Game &game) override;

        void OnShutdown(Game &engine);*/

        [[maybe_unused]] [[nodiscard]] const glm::vec3 &getDirectionalLightPositionAtIndex(int index) const;

        [[maybe_unused]] void setDirectionalLightPosition(glm::vec3 &directionalLightPosition);

        [[maybe_unused]] [[nodiscard]] const std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>> &getSceneModelAtIndex(int index) const;

        [[maybe_unused]] void AddSceneModels(const Model& model, const Graphics::shader* shader, Graphics::Transform* modelMatrix);

        [[nodiscard]] Camera *getCamera();

    private:
        void DisplayLights();
        void DisplayModels();

        vector<std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>>> sceneModels;
        Camera camera;
        vector<glm::vec3> directionalLightPositions;
        SkyboxRenderer skyboxRenderer {};

    };
}
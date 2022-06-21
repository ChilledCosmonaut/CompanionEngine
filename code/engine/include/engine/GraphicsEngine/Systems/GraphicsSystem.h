#pragma once

#include <iostream>

#include "engine/GraphicsEngine/Components/Model.h"
#include "engine/GraphicsEngine/Components/Camera.h"
#include "engine/GraphicsEngine/Components/Transform.h"

#include "engine/FileManager/FileManager.h"
#include "SkyboxRenderer.h"
#include "engine/EntityComponentSystem/System.h"
#include "ModelRenderer.h"

namespace gl3::engine::Graphics::Systems{

    class GraphicsSystem : public entityComponentSystem::System {
    public:
        GraphicsSystem() = default;

        void OnSwitchingScenes(Scene &scene) override {
            skyboxRenderer.SetupSkybox(scene);
            modelRenderer.SetUpModel(scene);
        }

        void OnDrawCall(Scene &scene) override;

        void Start(Game &game) override {};

        void Update(Game &game) override {};

        void OnShutdown(Game &engine) override {};

        /*[[maybe_unused]] [[nodiscard]] const glm::vec3 &getDirectionalLightPositionAtIndex(int index) const;

        [[maybe_unused]] void setDirectionalLightPosition(glm::vec3 &directionalLightPosition);

        [[maybe_unused]] [[nodiscard]] const std::pair<Components::Model, std::pair<const Graphics::shader *, Graphics::Components::Transform *>> &getSceneModelAtIndex(int index) const;

        [[maybe_unused]] void AddSceneModels(const Components::Model& model, const Graphics::shader* shader, Graphics::Components::Transform* modelMatrix);

        [[nodiscard]] Camera *getCamera();*/

    private:
        /*void DisplayLights();
        void DisplayModels();*/

        //vector<std::pair<Components::Model, std::pair<const Graphics::shader *, Graphics::Components::Transform *>>> sceneModels;
        //vector<glm::vec3> directionalLightPositions;
        glm::mat4 currentProjection;
        glm::mat4 currentView;
        SkyboxRenderer skyboxRenderer {};
        ModelRenderer modelRenderer {};
    };
}
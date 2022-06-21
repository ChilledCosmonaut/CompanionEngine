#include "engine/GraphicsEngine/Systems/GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    void GraphicsSystem::OnDrawCall(Scene &scene) {
        currentProjection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

        auto mainCamera = scene.getMainCamera();
        auto currentRegistry = scene.getRegistry();
        auto& mainCameraComponent = currentRegistry->get<Components::CameraComponent>(mainCamera);
        auto& mainCameraTransform = currentRegistry->get<Components::Transform>(mainCamera);
        currentView = Components::CameraUtils::GetViewMatrix(
                mainCameraComponent,
                mainCameraTransform);

        skyboxRenderer.Render(scene, currentView, currentProjection);

        //DisplayLights();

        modelRenderer.Render(scene, currentView, currentProjection, mainCameraTransform.GetTranslation());

    }/*
    [[maybe_unused]] const std::pair<Components::Model, std::pair<const Graphics::shader *, Graphics::Components::Transform *>> &GraphicsSystem::getSceneModelAtIndex(int index) const {
        return sceneModels[index];
    }

    [[maybe_unused]] void GraphicsSystem::AddSceneModels(const Components::Model& model, const Graphics::shader* shader, Graphics::Components::Transform* transform) {
        std::pair<const Graphics::shader *, Graphics::Components::Transform *> temporary(shader, transform);
        std::pair<Components::Model, std::pair<const Graphics::shader *, Graphics::Components::Transform *>> sceneModel(model, temporary);
        GraphicsSystem::sceneModels.push_back(sceneModel);
    }

    Camera *GraphicsSystem::getCamera() {
        return &camera;
    }*/
}


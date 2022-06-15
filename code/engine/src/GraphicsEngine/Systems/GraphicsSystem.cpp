#include "engine/GraphicsEngine/Systems/GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    void GraphicsSystem::OnDrawCall(Scene &scene) {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1920.0f / 1080.0f, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();

        skyboxRenderer.Render(scene, view, projection);

        //DisplayLights();

        modelRenderer.Render(scene, view, projection);

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


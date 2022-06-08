#include "engine/GraphicsEngine/Systems/GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);

    void GraphicsSystem::Update(Game &game) {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1920.0f / 1080.0f, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        auto currentScene = game.getCurrentScene();

        skyboxRenderer.render(*currentScene, view, projection);

        DisplayLights();
        DisplayModels();
    }

    void GraphicsSystem::DisplayLights() {

    }

    void GraphicsSystem::DisplayModels() {
        for (auto &[model, shaderAndTransform] : sceneModels) {
            if(!shaderAndTransform.second->IsActive()) continue;
            shaderAndTransform.first->use();
            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1920.0f / 1080.0f, 0.1f, 1000.0f);
            glm::mat4 view = camera.GetViewMatrix();
            shaderAndTransform.first->setMatrix("projection", projection);
            shaderAndTransform.first->setMatrix("view", view);

            shaderAndTransform.first->setMatrix("model", *shaderAndTransform.second->GetModelMatrix());

            shaderAndTransform.first->setVector("viewPos",glm::vec4(camera.Position, 1.0f));

            shaderAndTransform.first->setVector3("dirLight.direction", -lightPos);

            shaderAndTransform.first->setVector3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            shaderAndTransform.first->setVector3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
            shaderAndTransform.first->setVector3("dirLight.specular", glm::vec3(0.7f, 0.7f, 0.7f));

            model.Draw((Graphics::shader &) shaderAndTransform);
        }
    }

    [[maybe_unused]] const glm::vec3 &GraphicsSystem::getDirectionalLightPositionAtIndex(int index) const {
        return directionalLightPositions[index];
    }

    [[maybe_unused]] void GraphicsSystem::setDirectionalLightPosition(glm::vec3 &directionalLightPosition) {
        GraphicsSystem::directionalLightPositions.push_back(directionalLightPosition);
    }

    [[maybe_unused]] const std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>> &GraphicsSystem::getSceneModelAtIndex(int index) const {
        return sceneModels[index];
    }

    [[maybe_unused]] void GraphicsSystem::AddSceneModels(const Model& model, const Graphics::shader* shader, Graphics::Transform* transform) {
        std::pair<const Graphics::shader *, Graphics::Transform *> temporary(shader, transform);
        std::pair<Model, std::pair<const Graphics::shader *, Graphics::Transform *>> sceneModel(model, temporary);
        GraphicsSystem::sceneModels.push_back(sceneModel);
    }

    Camera *GraphicsSystem::getCamera() {
        return &camera;
    }
}


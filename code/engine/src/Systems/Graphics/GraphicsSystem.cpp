#include "GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    void GraphicsSystem::Update() {
        auto projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

        auto& registry = Ecs::Registry::getCurrent();

        glm::mat4 viewMatrix;
        glm::vec3 cameraTranslation;

        auto cameraView = registry.view<Graphics::Components::CameraComponent, Graphics::Components::Transform>();

        for (auto &&[entity, camera, transform] : cameraView.each()) {
            viewMatrix = Utils::CameraUtils::GetViewMatrix(camera,transform);
            cameraTranslation = transform.translation;
        }

        auto skyboxView = registry.view<Components::SkyboxComponent>();

        for (auto &&[entity, skybox]: skyboxView.each()) {

            glDepthMask(GL_FALSE);
            skybox.shader->use();
            skybox.shader->setMatrix("projection", projectionMatrix);
            skybox.shader->setMatrix("view", glm::mat3(viewMatrix));
            glBindVertexArray(skybox.VAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.texture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
        }

        //DisplayLights();

        auto modelView = registry.view<Components::Model, Components::Transform>();

        for(auto &&[entity, model, transform] : modelView.each()){
            if(!transform.active) continue;
            model.shader->use();

            model.shader->setMatrix("projection", projectionMatrix);
            model.shader->setMatrix("view", viewMatrix);

            model.shader->setMatrix("model", transform.modelMatrix);

            model.shader->setVector("viewPos",glm::vec4(cameraTranslation, 1.0f));

            model.shader->setVector3("dirLight.direction", -lightPos);

            model.shader->setVector3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
            model.shader->setVector3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
            model.shader->setVector3("dirLight.specular", glm::vec3(0.7f, 0.7f, 0.7f));

            Draw(model);
        }
    }

    void GraphicsSystem::Draw(Components::Model &modelData) {
        for (auto &mesh: modelData.meshes)
            mesh.Draw(*modelData.shader);

    }
}


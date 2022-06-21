#include "GraphicsSystem.h"

namespace gl3::engine::Graphics::Systems{

    void GraphicsSystem::OnDrawCall(Scene &scene) {
        currentProjection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

        auto mainCamera = scene.getMainCamera();
        auto currentRegistry = scene.getRegistry();
        auto& mainCameraComponent = currentRegistry->get<Components::CameraComponent>(mainCamera);
        auto& mainCameraTransform = currentRegistry->get<Components::Transform>(mainCamera);
        currentView = Utils::CameraUtils::GetViewMatrix(
                mainCameraComponent,
                mainCameraTransform);

        Utils::SkyboxUtils::Render(scene, currentView, currentProjection);

        //DisplayLights();

        Utils::ModelUtils::Render(scene, currentView, currentProjection, Utils::TransformUtils::GetTranslation(mainCameraTransform));
    }
}


#include "TransformSystem.h"

namespace gl3::engine::Graphics {

    TransformSystem *TransformSystem::GetTransformSystem() {
        if (transformSystem == nullptr)
            transformSystem = new TransformSystem();
        return transformSystem;
    }

    void TransformSystem::DestroyTransformSystem() {
        transformSystem->~TransformSystem();
        transformSystem = nullptr;
    }

    void TransformSystem::SetupTransform() {
        auto& registry = Ecs::Registry::getCurrent();

        auto setUpTransforms = registry.view<Transform, Ecs::Flags::Setup<Transform>>();

        for (auto entity : setUpTransforms) {
            auto& transform = setUpTransforms.get<Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveSetupFlag<Transform>(entity);
        }
    }

    void TransformSystem::UpdateTransform() {
        auto& registry = Ecs::Registry::getCurrent();

        auto updateTransforms = registry.view<Transform, Ecs::Flags::Update<Transform>>();

        for (auto entity : updateTransforms) {
            auto& transform = updateTransforms.get<Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveUpdateFlag<Transform>(entity);
        }
    }

    void TransformSystem::DestroyTransform() {
        auto& registry = Ecs::Registry::getCurrent();

        auto transformsForDestruction = registry.view<Transform, Ecs::Flags::Destroy<Transform>>();

        for (auto entity : transformsForDestruction) {
            auto& transform = transformsForDestruction.get<Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveDestroyFlag<Transform>(entity);
        }
    }

    void TransformSystem::RecalculateMatrices(Transform& transform) {

        auto& registry = Ecs::Registry::getCurrent();

        glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), transform.translation);
        glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -transform.translation);
        glm::mat4 rotateModel = glm::mat4_cast(transform.rotation);
        glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), transform.scale);
        glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/transform.scale.x, 1/transform.scale.y, 1/transform.scale.z));
        transform.modelMatrix = translateModel * rotateModel * scaleModel;
        transform.inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;

        if (transform.parent != entt::null){
            auto &parentTransform = registry.get<Transform>(transform.parent);
            transform.modelMatrix = parentTransform.modelMatrix * transform.modelMatrix;
            transform.inverseModelMatrix = transform.inverseModelMatrix * parentTransform.inverseModelMatrix;
            transform.globalRotation = parentTransform.globalRotation * transform.rotation;
        } else{
            transform.globalRotation = transform.rotation;
        }

        auto transformView = registry.view<Transform>();
        for (auto child:transform.children) {
            if(transformView.contains(child)){
                auto &childTransform = transformView.get<Transform>(child);
                RecalculateMatrices(childTransform);
            }
        }
    }
}
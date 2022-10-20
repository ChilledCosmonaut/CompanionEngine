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

        auto setUpTransforms = registry.view<Components::Transform, Ecs::Flags::Setup<Components::Transform>>();

        for (auto entity : setUpTransforms) {
            auto transform = setUpTransforms.get<Components::Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveSetupFlag<Components::Transform>(entity);
        }
    }

    void TransformSystem::UpdateTransform() {
        auto& registry = Ecs::Registry::getCurrent();

        auto updateTransforms = registry.view<Components::Transform, Ecs::Flags::Update<Components::Transform>>();

        for (auto entity : updateTransforms) {
            auto transform = updateTransforms.get<Components::Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveUpdateFlag<Components::Transform>(entity);
        }
    }

    void TransformSystem::DestroyTransform() {
        auto& registry = Ecs::Registry::getCurrent();

        auto transformsForDestruction = registry.view<Components::Transform, Ecs::Flags::Destroy<Components::Transform>>();

        for (auto entity : transformsForDestruction) {
            auto transform = transformsForDestruction.get<Components::Transform>(entity);
            RecalculateMatrices(transform);
            Ecs::Registry::RemoveDestroyFlag<Components::Transform>(entity);
        }
    }

    void TransformSystem::RecalculateMatrices(Components::Transform &transform) {

        auto& registry = Ecs::Registry::getCurrent();

        glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), transform.translation);
        glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -transform.translation);
        glm::mat4 rotateModel = glm::mat4_cast(transform.rotation);
        glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), transform.scale);
        glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/transform.scale.x, 1/transform.scale.y, 1/transform.scale.z));
        transform.modelMatrix = translateModel * rotateModel * scaleModel;
        transform.inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;

        if (transform.parent != entt::null){
            /*transform.modelMatrix = transform.parentModelMatrix * transform.modelMatrix;
            transform.inverseModelMatrix = transform.inverseModelMatrix * transform.parentInverseModelMatrix;*/
            auto &parentTransform = registry.get<Components::Transform>(transform.parent);
            transform.modelMatrix = parentTransform.modelMatrix * transform.modelMatrix;
            transform.inverseModelMatrix = transform.inverseModelMatrix * parentTransform.inverseModelMatrix;
        }

        auto transformView = registry.view<Components::Transform>();
        for (auto child:transform.children) {
            if(transformView.contains(child)){
                auto &childTransform = transformView.get<Components::Transform>(child);
                RecalculateMatrices(childTransform);
            }
        }
    }
}
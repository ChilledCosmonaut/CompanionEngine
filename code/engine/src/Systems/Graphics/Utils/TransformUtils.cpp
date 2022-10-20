#include "engine/Systems/Graphics/Utils/TransformationUtils.h"

namespace gl3::engine::Graphics::Utils {
    void TransformationUtils::AddChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity) {

        auto& registry = Ecs::Registry::getCurrent();

        transform.children.emplace_back(childEntity);
        auto &childTransform = registry.get<Components::Transform>(childEntity);

        if (childTransform.parent != entt::null){
            auto &childParentTransform = registry.get<Components::Transform>(childTransform.parent);
            RemoveChildEntity(childParentTransform, childTransform.parent, childEntity);
        }
        childTransform.parent = currentEntity;
        childTransform.parentModelMatrix = transform.modelMatrix;
        childTransform.parentInverseModelMatrix = transform.inverseModelMatrix;

        Ecs::Registry::UpdateComponent<Components::Transform>(childEntity);
    }

    void TransformationUtils::RemoveChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity) {
        auto& registry = Ecs::Registry::getCurrent();
        auto targetEntity = find(transform.children.begin(), transform.children.end(), childEntity);
        if (targetEntity != transform.children.end()){
            transform.children.erase(targetEntity);

            auto &targetTransform = registry.get<Components::Transform>(childEntity);
            targetTransform.parent = entt::null;
        }
    }

    void TransformationUtils::SetRotation(entt::entity entity, Components::Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::radians(targetRotation));
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::SetRotation(entt::entity entity, Components::Transform &transform, glm::quat targetRotation) {
        transform.rotation = targetRotation;
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::AddRotation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveRotation) {
        transform.rotation *= glm::quat(glm::radians(additiveRotation));
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::SetRotationFromGlobal(entt::entity entity, Components::Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::vec4(glm::radians(targetRotation), 0) * transform.parentInverseModelMatrix);
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::SetTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 targetTranslation) {
        transform.translation = targetTranslation;
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::AddTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = transform.translation + additiveTranslation;
        SetTranslation(entity, transform, newTranslation);
    }

    void TransformationUtils::AddRelativeTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = transform.translation + (transform.rotation * additiveTranslation);
        SetTranslation(entity, transform, newTranslation);
    }

    void TransformationUtils::SetTranslationFromGlobal(entt::entity entity, Components::Transform &transform, glm::vec3 globalTranslation) {
        glm::vec3 newTranslation = glm::vec4(transform.translation, 1.) * transform.parentInverseModelMatrix;
        SetTranslation(entity, transform, newTranslation);
    }

    void TransformationUtils::SetScale(entt::entity entity, Components::Transform &transform, glm::vec3 targetScale) {
        transform.scale = targetScale;
        Ecs::Registry::UpdateComponent<Components::Transform>(entity);
    }

    void TransformationUtils::AddScale(entt::entity entity, Components::Transform &transform, glm::vec3 additiveScale) {
        glm::vec3 newScale = transform.scale + additiveScale;
        SetScale(entity, transform, newScale);
    }

    void TransformationUtils::RotateTowardsPosition(Components::Transform &transform, glm::vec3 position) {

        transform.rotation = glm::toQuat(
                glm::inverse(
                        glm::lookAt(
                                position,
                                transform.translation,
                                glm::vec3(0, 1, 0))))/* * glm::quat(glm::radians(glm::vec3(0, 90, 0)))*/;
    }

    glm::vec3 TransformationUtils::ProjectOntoPlane(Components::Transform &transform, glm::vec3 vector, glm::vec3 planeNormal) {
        glm::vec3 projectedOntoNormal = ((vector * planeNormal)/(float)pow(glm::length(planeNormal),2));
        return vector - planeNormal;
    }
}
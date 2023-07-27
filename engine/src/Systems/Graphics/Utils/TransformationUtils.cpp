#include <iostream>
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"

namespace gl3::engine::Graphics{

    glm::mat4 TransformationUtils::GetViewMatrix(Camera &camera, Transform &transform) {
        return camera.lookAtMatrix * transform.inverseModelMatrix;
    }

    void TransformationUtils::AddChildEntity(entt::entity parentEntity, entt::entity childEntity) {

        auto& registry = Ecs::Registry::getCurrent();
        auto &childTransform = registry.get<Transform>(childEntity);
        auto &parentTransform = registry.get<Transform>(parentEntity);

        parentTransform.children.emplace_back(childEntity);

        if (childTransform.parent != entt::null){
            auto &childParentTransform = registry.get<Transform>(childTransform.parent);
            RemoveChildEntity(childParentTransform, childTransform.parent, childEntity);
        }
        childTransform.parent = parentEntity;

        Ecs::Registry::UpdateComponent<Transform>(childEntity);
    }

    void TransformationUtils::RemoveChildEntity(Transform &transform, entt::entity currentEntity, entt::entity childEntity) {
        auto& registry = Ecs::Registry::getCurrent();
        auto targetEntity = find(transform.children.begin(), transform.children.end(), childEntity);
        if (targetEntity != transform.children.end()){
            transform.children.erase(targetEntity);

            auto &targetTransform = registry.get<Transform>(childEntity);
            targetTransform.parent = entt::null;
        }
    }

    void TransformationUtils::SetRotation(entt::entity entity, Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::radians(targetRotation));
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    void TransformationUtils::SetRotation(entt::entity entity, Transform &transform, glm::quat targetRotation) {
        transform.rotation = targetRotation;
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    void TransformationUtils::AddRotation(entt::entity entity, Transform &transform, glm::vec3 additiveRotation) {
        transform.rotation *= glm::quat(glm::radians(additiveRotation));
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    void TransformationUtils::SetRotationFromGlobal(entt::entity entity, Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::vec4(glm::radians(targetRotation), 0) * transform.parentInverseModelMatrix);
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    glm::vec3 TransformationUtils::GetGlobalRotation(Transform &transform) {
        return glm::eulerAngles(transform.globalRotation);
    }

    void TransformationUtils::SetTranslation(entt::entity entity, Transform &transform, glm::vec3 targetTranslation) {
        transform.translation = targetTranslation;
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    void TransformationUtils::AddTranslation(entt::entity entity, Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = transform.translation + additiveTranslation;
        SetTranslation(entity, transform, newTranslation);
    }

    void TransformationUtils::AddRelativeTranslation(entt::entity entity, Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = transform.translation + (transform.rotation * additiveTranslation);
        SetTranslation(entity, transform, newTranslation);
    }

    void TransformationUtils::SetTranslationFromGlobal(entt::entity entity, Transform &transform, glm::vec3 globalTranslation) {
        glm::vec3 newTranslation = glm::vec4(transform.translation, 1.) * transform.parentInverseModelMatrix;
        SetTranslation(entity, transform, newTranslation);
    }

    glm::vec3 TransformationUtils::GetGlobalTranslation(Transform &transform) {
        return transform.modelMatrix * glm::vec4(0, 0, 0, 1);
    }

    void TransformationUtils::SetScale(entt::entity entity, Transform &transform, glm::vec3 targetScale) {
        transform.scale = targetScale;
        Ecs::Registry::UpdateComponent<Transform>(entity);
    }

    void TransformationUtils::AddScale(entt::entity entity, Transform &transform, glm::vec3 additiveScale) {
        glm::vec3 newScale = transform.scale + additiveScale;
        SetScale(entity, transform, newScale);
    }

    void TransformationUtils::RotateTowardsPosition(Transform &transform, glm::vec3 position) {

        transform.rotation = glm::toQuat(
                glm::inverse(
                        glm::lookAt(
                                position,
                                transform.translation,
                                glm::vec3(0, 1, 0))))/* * glm::quat(glm::radians(glm::vec3(0, 90, 0)))*/;
    }

    glm::vec3 TransformationUtils::ProjectOntoPlane(Transform &transform, glm::vec3 vector, glm::vec3 planeNormal) {
        glm::vec3 projectedOntoNormal = ((vector * planeNormal)/(float)pow(glm::length(planeNormal),2));
        return vector - planeNormal;
    }
}
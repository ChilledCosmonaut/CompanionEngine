#include "engine/Systems/Graphics/Utils/TransformUtils.h"

namespace gl3::engine::Graphics::Utils {
    void TransformUtils::AddChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity) {
        transform.children.emplace_back(childEntity);
        auto &childTransform = transform.currentRegistry->get<Components::Transform>(childEntity);

        if (childTransform.parent != entt::null){
            auto &childParentTransform = transform.currentRegistry->get<Components::Transform>(childTransform.parent);
            RemoveChildEntity(childParentTransform, childTransform.parent, childEntity);
        }
        childTransform.parent = currentEntity;
        childTransform.parentModelMatrix = transform.modelMatrix;
        childTransform.parentInverseModelMatrix = transform.inverseModelMatrix;
    }

    void TransformUtils::RemoveChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity) {
        auto targetEntity = find(transform.children.begin(), transform.children.end(), childEntity);
        if (targetEntity != transform.children.end()){
            transform.children.erase(targetEntity);

            auto &targetTransform = transform.currentRegistry->get<Components::Transform>(childEntity);
            targetTransform.parent = entt::null;
        }
    }

    void TransformUtils::SetCurrentRegistry(Components::Transform &transform, entt::registry &registry) {
        transform.currentRegistry = &registry;
    }

    void TransformUtils::SetRotation(Components::Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::radians(targetRotation));
        recalculateModel(transform);
    }

    void TransformUtils::SetRotation(Components::Transform &transform, glm::quat targetRotation) {
        transform.rotation = targetRotation;
        recalculateModel(transform);
    }

    void TransformUtils::AddRotation(Components::Transform &transform, glm::vec3 additiveRotation) {
        transform.rotation *= glm::quat(glm::radians(additiveRotation));
        recalculateModel(transform);
    }

    void TransformUtils::SetRotationFromGlobal(Components::Transform &transform, glm::vec3 targetRotation) {
        transform.rotation = glm::quat(glm::vec4(glm::radians(targetRotation), 0) * transform.parentInverseModelMatrix);
        recalculateModel(transform);
    }

    glm::vec3 TransformUtils::GetRotation(Components::Transform &transform) {
        return glm::degrees(glm::eulerAngles(transform.rotation));
    }

    glm::vec3 TransformUtils::GetGlobalRotation(Components::Transform &transform) {
        return transform.parentModelMatrix * glm::vec4(glm::degrees(glm::eulerAngles(transform.rotation)),0);
    }

    glm::quat TransformUtils::GetQuatRotation(Components::Transform &transform) {
        return transform.rotation;
    }

    void TransformUtils::SetTranslation(Components::Transform &transform, glm::vec3 targetTranslation) {
        transform.translation = targetTranslation;
        recalculateModel(transform);
    }

    void TransformUtils::AddTranslation(Components::Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = GetTranslation(transform) + additiveTranslation;
        SetTranslation(transform, newTranslation);
    }

    void TransformUtils::AddRelativeTranslation(Components::Transform &transform, glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = GetTranslation(transform) + (transform.rotation * additiveTranslation);
        SetTranslation(transform, newTranslation);
    }

    void TransformUtils::SetTranslationFromGlobal(Components::Transform &transform, glm::vec3 globalTranslation) {
        glm::vec3 newTranslation = glm::vec4(transform.translation, 0) * transform.parentInverseModelMatrix;
        SetTranslation(transform, newTranslation);
    }

    glm::vec3 TransformUtils::GetTranslation(Components::Transform &transform) {
        return transform.translation;
    }

    glm::vec3 TransformUtils::GetGlobalTranslation(Components::Transform &transform) {
        return transform.parentModelMatrix * glm::vec4(transform.translation, 0);
    }

    void TransformUtils::SetScale(Components::Transform &transform, glm::vec3 targetScale) {
        transform.scale = targetScale;
        recalculateModel(transform);
    }

    void TransformUtils::AddScale(Components::Transform &transform, glm::vec3 additiveScale) {
        glm::vec3 newScale = GetScale(transform) + additiveScale;
        SetScale(transform, newScale);
    }

    glm::vec3 TransformUtils::GetScale(Components::Transform &transform) {
        return transform.scale;
    }

    glm::mat4 TransformUtils::GetModelMatrix(Components::Transform &transform) {
        return transform.modelMatrix;
    }

    glm::mat4 TransformUtils::GetInverseModelMatrix(Components::Transform &transform) {
        return transform.inverseModelMatrix;
    }

    void TransformUtils::recalculateModel(Components::Transform &transform) {
        glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), transform.translation);
        glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -transform.translation);
        glm::mat4 rotateModel = glm::mat4_cast(transform.rotation);
        glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), transform.scale);
        glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/transform.scale.x, 1/transform.scale.y, 1/transform.scale.z));
        transform.modelMatrix = translateModel * rotateModel * scaleModel;
        transform.inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;

        if (transform.parent != entt::null){
            transform.modelMatrix = transform.parentModelMatrix * transform.modelMatrix;
            transform.inverseModelMatrix = transform.inverseModelMatrix * transform.parentInverseModelMatrix;
        }

        auto transformView = transform.currentRegistry->view<Components::Transform>();
        for (auto child:transform.children) {
            if(transformView.contains(child)){
                auto &childTransform = transformView.get<Components::Transform>(child);
                recalculateModel(childTransform);
            }
        }
    }

    bool TransformUtils::IsActive(Components::Transform &transform) {
        return transform.active;
    }

    void TransformUtils::SetActive(Components::Transform &transform, bool active) {
        transform.active = active;
    }

    void TransformUtils::RotateTowardsPosition(Components::Transform &transform, glm::vec3 position) {

        transform.rotation = glm::toQuat(
                glm::inverse(
                        glm::lookAt(
                                position,
                                transform.translation,
                                glm::vec3(0, 1, 0))))/* * glm::quat(glm::radians(glm::vec3(0, 90, 0)))*/;
        recalculateModel(transform);
    }

    glm::vec3 TransformUtils::ProjectOntoPlane(Components::Transform &transform, glm::vec3 vector, glm::vec3 planeNormal) {
        glm::vec3 projectedOntoNormal = ((vector * planeNormal)/(float)pow(glm::length(planeNormal),2));
        return vector - planeNormal;
    }
}
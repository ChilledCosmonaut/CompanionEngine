#include "Transform.h"

namespace Graphics {

    Transform::Transform(glm::vec3 startRotation, glm::vec3 startTranslation, glm::vec3 startScale) {
        //Translation and Scale are set directly here to minimize Matrix recalculation
        translation = startTranslation;
        scale = startScale;
        SetRotation(startRotation);
    }

    void Transform::SetRotation(glm::vec3 targetRotation) {
        rotation = glm::quat(glm::radians(targetRotation));
        recalculateModel();
    }

    void Transform::AddRotation(glm::vec3 additiveRotation) {
        rotation *= glm::quat(glm::radians(additiveRotation));
        recalculateModel();
    }

    glm::vec3 Transform::GetRotation() {
        return glm::degrees(glm::eulerAngles(rotation));
    }

    void Transform::SetTranslation(glm::vec3 targetTranslation) {
        translation = targetTranslation;
        recalculateModel();
    }

    void Transform::AddTranslation(glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = GetTranslation() + additiveTranslation;
        SetTranslation(newTranslation);
    }

    void Transform::AddRelativeTranslation(glm::vec3 additiveTranslation) {
        glm::vec3 newTranslation = GetTranslation() + (rotation * additiveTranslation);
        SetTranslation(newTranslation);
    }

    glm::vec3 Transform::GetTranslation() {
        return translation;
    }

    void Transform::SetScale(glm::vec3 targetScale) {
        scale = targetScale;
        recalculateModel();
    }

    void Transform::AddScale(glm::vec3 additiveScale) {
        glm::vec3 newScale = GetScale() + additiveScale;
        SetScale(newScale);
    }

    glm::vec3 Transform::GetScale() {
        return scale;
    }

    glm::mat4* Transform::GetModelMatrix() {
        return &modelMatrix;
    }

    glm::mat4 Transform::GetInverseModelMatrix() {
        return inverseModelMatrix;
    }

    void Transform::recalculateModel() {
        glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -translation);
        glm::mat4 rotateModel = glm::mat4_cast(rotation);
        glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/scale.x, 1/scale.y, 1/scale.z));
        modelMatrix = translateModel * rotateModel * scaleModel;
        inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;
    }

    bool Transform::IsActive() {
        return active;
    }

    void Transform::SetActive(bool active) {
        this->active = active;
    }
}
#pragma once

#include "engine/GraphicsEngine/Components/Transform.h"

namespace gl3::engine::Graphics::Utils {
    class TransformUtils{
    public:
        static void AddChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity);
        static void RemoveChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity);
        static void SetCurrentRegistry(Components::Transform &transform, entt::registry &registry);

        static void SetRotation(Components::Transform &transform, glm::vec3 targetRotation);
        static void SetRotation(Components::Transform &transform, glm::quat targetRotation);
        static void AddRotation(Components::Transform &transform, glm::vec3 additiveRotation);
        static glm::vec3 GetRotation(Components::Transform &transform);

        static void SetTranslation(Components::Transform &transform, glm::vec3 targetTranslation);
        static void AddTranslation(Components::Transform &transform, glm::vec3 additiveTranslation);
        static void AddRelativeTranslation(Components::Transform &transform, glm::vec3 additiveTranslation);
        static glm::vec3 GetTranslation(Components::Transform &transform);

        static void SetScale(Components::Transform &transform, glm::vec3 targetScale);
        static void AddScale(Components::Transform &transform, glm::vec3 additiveScale);
        static glm::vec3 GetScale(Components::Transform &transform);

        static bool IsActive(Components::Transform &transform);
        static void SetActive(Components::Transform &transform, bool active);

        static glm::mat4 GetModelMatrix(Components::Transform &transform);
        static glm::mat4 GetInverseModelMatrix(Components::Transform &transform);

        /// Rotates the current transform towards an arbitrary position.
        /// @param position Position to which the transform will be rotate to.
        static void RotateTowardsPosition(Components::Transform &transform, glm::vec3 position);

        /// Projects an arbitrary vector onto a plane defined by a plane normal.
        /// @param vector The vectored to be projected onto the plane.
        /// @param planeNormal The normal defining the plane on which the projection will take place.
        /// @return Returns the projected vector as copy.
        static glm::vec3 ProjectOntoPlane(Components::Transform &transform, glm::vec3 vector, glm::vec3 planeNormal);

    private:
        static void recalculateModel(Components::Transform &transform);
    };
}
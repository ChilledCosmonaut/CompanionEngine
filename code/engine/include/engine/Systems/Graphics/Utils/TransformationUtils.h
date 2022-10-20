#pragma once

#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/ECS/Registry.h"

namespace gl3::engine::Graphics::Utils {
    class TransformationUtils{
    public:
        static void AddChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity);
        static void RemoveChildEntity(Components::Transform &transform, entt::entity currentEntity, entt::entity childEntity);

        static void SetRotation(entt::entity entity, Components::Transform &transform, glm::vec3 targetRotation);
        static void SetRotation(entt::entity entity, Components::Transform &transform, glm::quat targetRotation);
        static void AddRotation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveRotation);
        static void SetRotationFromGlobal(entt::entity entity, Components::Transform &transform, glm::vec3 targetRotation);

        static void SetTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 targetTranslation);
        static void AddTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveTranslation);
        static void AddRelativeTranslation(entt::entity entity, Components::Transform &transform, glm::vec3 additiveTranslation);
        static void SetTranslationFromGlobal(entt::entity entity, Components::Transform &transform, glm::vec3 globalTranslation);

        static void SetScale(entt::entity entity, Components::Transform &transform, glm::vec3 targetScale);
        static void AddScale(entt::entity entity, Components::Transform &transform, glm::vec3 additiveScale);

        /// Rotates the current transform towards an arbitrary position.
        /// @param position Position to which the transform will be rotate to.
        static void RotateTowardsPosition(Components::Transform &transform, glm::vec3 position);

        /// Projects an arbitrary vector onto a plane defined by a plane normal.
        /// @param vector The vectored to be projected onto the plane.
        /// @param planeNormal The normal defining the plane on which the projection will take place.
        /// @return Returns the projected vector as copy.
        static glm::vec3 ProjectOntoPlane(Components::Transform &transform, glm::vec3 vector, glm::vec3 planeNormal);
    };
}
#pragma once

#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Components/Camera.h"

namespace gl3::engine::Graphics {
    /**
     * Utils class with helper functions for CG math.
     * Allows to easily access common CG calculations.
     */
    class TransformationUtils{
    public:
        /**
         * Returns a matrix for a camera component.
         * @param camera Camera component
         * @param transform Transform component of the camera
         * @return Right hand LookAt Matrix for the camera
         */
        static glm::mat4 GetViewMatrix(Camera &camera, Transform &transform);

        /**
         * Adds a child entity to a specified parent entity.
         * Child transform is now als transformed by the parent transform.
         * @param parentEntity Parent Entity
         * @param childEntity Child Entity
         */
        static void AddChildEntity(entt::entity parentEntity, entt::entity childEntity);
        /**
         * Removes a child entity to a specified parent entity.
         * @param transform Transform of parent
         * @param currentEntity Parent entity
         * @param childEntity Child entity
         */
        static void RemoveChildEntity(Transform &transform, entt::entity currentEntity, entt::entity childEntity);

        /**
         * Sets rotation via euler angles
         * @param entity Entity of transform
         * @param transform Transform to which rotation should be applied
         * @param targetRotation New rotation
         */
        static void SetRotation(entt::entity entity, Transform &transform, glm::vec3 targetRotation);
        /**
         * Sets rotation via quaternion
         * @param entity Entity of transform
         * @param transform Transform to which rotation should be applied
         * @param targetRotation New rotation
         */
        static void SetRotation(entt::entity entity, Transform &transform, glm::quat targetRotation);
        /**
         * Adds rotation relative to the current rotation in euler angles
         * @param entity Entity of transform
         * @param transform Transform to which rotation should be applied
         * @param additiveRotation Additive rotation
         */
        static void AddRotation(entt::entity entity, Transform &transform, glm::vec3 additiveRotation);
        /**
         * Sets rotation via euler angles in global space
         * @param entity Entity of transform
         * @param transform Transform to which rotation should be applied
         * @param targetRotation New rotation in global space
         */
        static void SetRotationFromGlobal(entt::entity entity, Transform &transform, glm::vec3 targetRotation);
        /**
         * Retrieves the global rotation of a transform
         * @param transform The transform to retrieve the rotation from
         * @return Global rotation in euler angles
         */
        static glm::vec3 GetGlobalRotation(Transform &transform);

        /**
         * Sets translation of a transform
         * @param entity Entity of the transform
         * @param transform Transform to be translated
         * @param targetTranslation New translation of transform
         */
        static void SetTranslation(entt::entity entity, Transform &transform, glm::vec3 targetTranslation);
        /**
         * Adds translation to a transform
         * @param entity Entity of the transform
         * @param transform Transform to be added to
         * @param additiveTranslation Additive translation
         */
        static void AddTranslation(entt::entity entity, Transform &transform, glm::vec3 additiveTranslation);
        /**
         * Adds translation of a transform with the current rotation
         * @param entity Entity of the transform
         * @param transform Transform to be added to
         * @param additiveTranslation Additive translation
         */
        static void AddRelativeTranslation(entt::entity entity, Transform &transform, glm::vec3 additiveTranslation);
        /**
         * Sets translation of a transform without considering any rotation
         * @param entity Entity of the transform
         * @param transform Transform to be translated
         * @param globalTranslation New global translation of transform
         */
        static void SetTranslationFromGlobal(entt::entity entity, Transform &transform, glm::vec3 globalTranslation);
        /**
         * Gets translation of a transform
         * @param transform Transform to retrieve translation from
         * @return Translation as vector in global space
         */
        static glm::vec3 GetGlobalTranslation(Transform &transform);

        /**
         * Sets the scale of a transform
         * @param entity Entity of the transform
         * @param transform Transform to be scaled
         * @param targetScale New scale of transform
         */
        static void SetScale(entt::entity entity, Transform &transform, glm::vec3 targetScale);
        /**
         * Adds scale to a transform
         * @param entity Entity of the transform
         * @param transform Transform to be added to
         * @param additiveScale Additive scale for the transform
         */
        static void AddScale(entt::entity entity, Transform &transform, glm::vec3 additiveScale);

        /// Rotates the current transform towards an arbitrary position.
        /// @param position Position to which the transform will be rotate to.
        static void RotateTowardsPosition(Transform &transform, glm::vec3 position);

        /// Projects an arbitrary vector onto a plane defined by a plane normal.
        /// @param vector The vectored to be projected onto the plane.
        /// @param planeNormal The normal defining the plane on which the projection will take place.
        /// @return Returns the projected vector as copy.
        static glm::vec3 ProjectOntoPlane(Transform &transform, glm::vec3 vector, glm::vec3 planeNormal);
    };
}
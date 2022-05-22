#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/dual_quaternion.hpp"

namespace Graphics {

    class Transform {
    public:
        explicit Transform(glm::vec3 startRotation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startTranslation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startScale = glm::vec3(1.0f,1.0f,1.0f));

        void SetRotation(glm::vec3 targetRotation);
        void SetRotation(glm::quat targetRotation);
        void AddRotation(glm::vec3 additiveRotation);
        glm::vec3 GetRotation();

        void SetTranslation(glm::vec3 targetTranslation);
        void AddTranslation(glm::vec3 additiveTranslation);
        void AddRelativeTranslation(glm::vec3 additiveTranslation);
        glm::vec3 GetTranslation();

        void SetScale(glm::vec3 targetScale);
        void AddScale(glm::vec3 additiveScale);
        glm::vec3 GetScale();

        bool IsActive();
        void SetActive(bool active);

        glm::mat4* GetModelMatrix();
        glm::mat4 GetInverseModelMatrix();

        /// Rotates the current transform towards an arbitrary position.
        /// @param position Position to which the transform will be rotate to.
        void RotateTowardsPosition(glm::vec3 position);

        /// Projects an arbitrary vector onto a plane defined by a plane normal.
        /// @param vector The vectored to be projected onto the plane.
        /// @param planeNormal The normal defining the plane on which the projection will take place.
        /// @return Returns the projected vector as copy.
        static glm::vec3 ProjectOntoPlane(glm::vec3 vector, glm::vec3 planeNormal);

    private:
        glm::vec3 translation{};
        glm::quat rotation{};
        glm::vec3 scale{};

        glm::mat4 modelMatrix{};
        glm::mat4 inverseModelMatrix{};

        bool active;

        void recalculateModel();
    };
}
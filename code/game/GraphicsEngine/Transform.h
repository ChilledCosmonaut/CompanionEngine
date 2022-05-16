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
        void AddRotation(glm::vec3 additiveRotation);
        glm::vec3 GetRotation();

        void SetTranslation(glm::vec3 targetTranslation);
        void AddTranslation(glm::vec3 additiveTranslation);
        void AddRelativeTranslation(glm::vec3 additiveTranslation);
        glm::vec3 GetTranslation();

        void SetScale(glm::vec3 targetScale);
        void AddScale(glm::vec3 additiveScale);
        glm::vec3 GetScale();

        glm::mat4* GetModelMatrix();
        glm::mat4 GetInverseModelMatrix();

    private:
        glm::vec3 translation{};
        glm::quat rotation{};
        glm::vec3 scale{};

        glm::mat4 modelMatrix{};
        glm::mat4 inverseModelMatrix{};

        void recalculateModel();
    };
}
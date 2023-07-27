#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "../../../../../src/ECS/entt.hpp"

namespace gl3::engine::Graphics {

    /**
     * Component for transform info.
     * Stores translation, rotation and scale. Data may also be manipulated by using the `TransformationUtils`
     */
    class Transform {
    public:
        explicit Transform(glm::vec3 startRotation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startTranslation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startScale = glm::vec3(1.0f,1.0f,1.0f)) {
            //Translation and Scale are set directly here to minimize Matrix recalculation
            translation = startTranslation;
            scale = startScale;
            rotation = glm::quat(startRotation);

            //Initial calculate matrices.... Sadly is a duplicate from the Util class
            /*glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -translation);
            glm::mat4 rotateModel = glm::mat4_cast(rotation);
            glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), scale);
            glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/scale.x, 1/scale.y, 1/scale.z));
            modelMatrix = translateModel * rotateModel * scaleModel;
            inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;*/
        }

        /// Translation stored as vector
        glm::vec3 translation{};
        /// Rotation stored as quaternion
        glm::quat rotation{};
        /// Separately stored parent rotation
        glm::quat parentRotation{};
        /// Complete global rotation
        glm::quat globalRotation{};
        /// Scale stored as vector **Setting a value to zero results in weird behaviour**
        glm::vec3 scale = glm::vec3(1,1,1);

        /// Calculated model matrix
        glm::mat4 modelMatrix{};
        /// Calculated inverse model matrix
        glm::mat4 inverseModelMatrix{};

        /// Calculated parent model matrix
        glm::mat4 parentModelMatrix{};
        /// Calculated parent inverse model matrix
        glm::mat4 parentInverseModelMatrix{};

        /// Parent entity
        entt::entity parent = entt::null;
        /// Child entity
        std::vector<entt::entity> children{};

        bool active;
    };
}
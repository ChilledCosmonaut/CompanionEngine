#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

namespace gl3::engine::Graphics::Utils {
    class TransformUtils;
}

namespace gl3::engine::Graphics::Components {
    class TransformUtils;

    class Transform {
        friend class Utils::TransformUtils;
    public:
        explicit Transform(glm::vec3 startRotation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startTranslation = glm::vec3(0.0f,0.0f,0.0f),
                           glm::vec3 startScale = glm::vec3(1.0f,1.0f,1.0f)) {
            //Translation and Scale are set directly here to minimize Matrix recalculation
            translation = startTranslation;
            scale = startScale;
            rotation = startRotation;

            //Initial calculate matrices.... Sadly is a duplicate from the Util class
            glm::mat4 translateModel = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 inverseTranslateModel = glm::translate(glm::mat4(1.0f), -translation);
            glm::mat4 rotateModel = glm::mat4_cast(rotation);
            glm::mat4 scaleModel = glm::scale(glm::mat4(1.0f), scale);
            glm::mat4 inverseScaleModel = glm::scale(glm::mat4(1.0f), glm::vec3(1/scale.x, 1/scale.y, 1/scale.z));
            modelMatrix = translateModel * rotateModel * scaleModel;
            inverseModelMatrix = inverseScaleModel * glm::inverse(rotateModel) * inverseTranslateModel;
        }

    private:
        glm::vec3 translation{};
        glm::quat rotation{};
        glm::vec3 scale = glm::vec3(1,1,1);

        glm::mat4 modelMatrix{};
        glm::mat4 inverseModelMatrix{};

        std::vector<entt::entity> childs{};

        bool active;
    };
}
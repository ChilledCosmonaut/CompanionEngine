#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics::Utils {
    class CameraUtils;
}

namespace gl3::engine::Graphics::Components {
    struct CameraComponent {
        friend class Utils::CameraUtils;

    public:
        CameraComponent() {
            lookAtMatrix = glm::lookAt(
                    glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        }

    private:
        glm::mat4 lookAtMatrix;
    };
}

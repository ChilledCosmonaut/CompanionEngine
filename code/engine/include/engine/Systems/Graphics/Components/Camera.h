#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    struct Camera {
    public:
        Camera() {
            lookAtMatrix = glm::lookAt(
                    glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        }

        glm::mat4 lookAtMatrix {};
    };
}

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Transform.h"

namespace gl3::engine::Graphics {

    /**
     * Component responsible for tracking camera data.
     * Used as a identifier component for the render system. **Strictly required in every scene**
     */
    struct Camera {
    public:
        Camera() {
            lookAtMatrix = glm::lookAtRH(
                    glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
        }

        glm::mat4 lookAtMatrix {};
    };
}

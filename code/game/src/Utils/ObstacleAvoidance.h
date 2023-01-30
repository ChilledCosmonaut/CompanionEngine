#pragma once

#include <glm/vec3.hpp>

#include <engine/Systems/Graphics/Components/Transform.h>

class ObstacleAvoidance {
public:
    static glm::vec3 getAvoidanceForce(gl3::engine::Graphics::Transform avoiderTransform, entt::registry registry);

private:
    static glm::vec3 getSingleAvoidanceForce(glm::vec3 avoider, glm::vec3 obstacle);
};

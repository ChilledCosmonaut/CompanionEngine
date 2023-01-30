#include "ObstacleAvoidance.h"

glm::vec3 ObstacleAvoidance::getAvoidanceForce(gl3::engine::Graphics::Transform avoiderTransform, entt::registry registry){
    glm::vec3 forceDirection = glm::vec3 ();

    auto obstacleView = registry.view<gl3::engine::Graphics::Transform>();
    for (auto &&[entity, obstacleTransform]: obstacleView.each())
        forceDirection += getSingleAvoidanceForce(avoiderTransform.translation, obstacleTransform.translation);

    return forceDirection;
}

glm::vec3 ObstacleAvoidance::getSingleAvoidanceForce(glm::vec3 avoider, glm::vec3 obstacle) {
    double magnitude = 1 / glm::pow(glm::distance(obstacle, avoider), 2);
    glm::vec3 direction = obstacle - avoider;
    glm::normalize(direction);
    direction *= magnitude;
    return direction;
}

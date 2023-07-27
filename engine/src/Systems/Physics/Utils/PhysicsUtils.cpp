#include "engine/Systems/Physics/Utils/PhysicsUtils.h"

entt::entity gl3::engine::Physics::PhysicsUtils::MakeRaycast(glm::vec3 origin, glm::vec3 direction, float maxDistance) {
    physx::PxRaycastBuffer hitInfo;
    PhysicsSystem *physicsSystem = PhysicsSystem::GetPhysicsSystem();

    direction = glm::normalize(direction);
    physx::PxVec3 pxOrigin = physx::PxVec3(origin.x, origin.y, origin.z);
    physx::PxVec3 pxDirection = physx::PxVec3(direction.x, direction.y, direction.z);

    bool hit = physicsSystem->mScene->raycast(pxOrigin, pxDirection, maxDistance, hitInfo);

    if (!hit)
        return entt::null;

    return physicsSystem->actorMap[hitInfo.block.actor];
}

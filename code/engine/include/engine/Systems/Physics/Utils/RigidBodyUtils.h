#pragma once

#include "PxPhysicsAPI.h"

#include "engine/Systems/Physics/Components/Rigidbody.h"
#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"
#include "engine/Systems/Physics/PhysicsSystem.h"
#include "engine/Time.h"
#include "engine/Scene.h"

#include <glm/gtc/matrix_access.hpp>

namespace gl3::engine::Physics::Utils {

    class RigidBodyUtils {
    public:

        static void AddForce(Components::RigidBody &rigidBody, glm::vec3 forceVector){
            rigidBody.rigidBody->addForce(physx::PxVec3(forceVector.x, forceVector.y, forceVector.z));
        }

        static void AddTorque(Components::RigidBody &rigidBody, glm::vec3 torqueVector){
            rigidBody.rigidBody->addTorque(physx::PxVec3(torqueVector.x, torqueVector.y, torqueVector.z));
        }

    private:
        inline static bool connected = false;

        static void ConnectCallbacks(Graphics::Scene &scene){
            scene.getRegistry()->on_construct<Components::RigidBody>().connect<&SetUpRigidBody>();
            scene.getRegistry()->on_construct<Components::RigidStatic>().connect<&SetUpRigidStatic>();
            connected = true;
        }
    };
}

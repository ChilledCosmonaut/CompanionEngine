#pragma once

#include "PxPhysicsAPI.h"

#include "engine/Systems/Physics/Components/RigidBody.h"
#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/Systems/Graphics/Utils/TransformUtils.h"
#include "engine/Systems/Physics/PhysicsSystem.h"
#include "engine/Time.h"
#include "engine/Systems/Graphics/Scene.h"

namespace gl3::engine::Physics::Utils {

    class RigidBodyUtils {
    public:
        static void SetUpRigidBody(entt::registry &registry, entt::entity entity){

            auto& rigidBody = registry.get<Components::RigidBody>(entity);
            auto& transform = registry.get<Graphics::Components::Transform>(entity);

            auto& physicsSystem = PhysicsSystem::GetPhysicsSystem();
            auto physicsContext = physicsSystem.GetPhysics();

            auto mMaterial =
                    physicsContext->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);

            physx::PxShape* shape;

            struct Components::Shapes::Sphere sphere;
            struct Components::Shapes::Box box;
            struct Components::Shapes::Capsule capsule;

            switch (rigidBody.shape) {
                case Components::Shapes::Sphere:
                    sphere = std::get<Components::Shapes::Sphere>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxSphereGeometry(sphere.radius)
                            , *mMaterial);
                    break;
                case Components::Shapes::Box:
                    box = std::get<Components::Shapes::Box>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxBoxGeometry(box.dimensions.x, box.dimensions.y, box.dimensions.z)
                            , *mMaterial);
                    break;
                case Components::Shapes::Capsule:
                    capsule = std::get<Components::Shapes::Capsule>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxCapsuleGeometry(capsule.radius, capsule.halfHeight), *mMaterial);
                    break;
                case Components::Shapes::Plane:
                    shape = physicsContext->createShape(physx::PxPlaneGeometry(), *mMaterial);
                    break;
            }

            auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

            physx::PxTransform currentColliderTransform(physx::PxVec3(translation.x, translation.y, translation.z));
            rigidBody.rigidBody = physicsContext->createRigidDynamic(currentColliderTransform);
            rigidBody.rigidBody->attachShape(*shape);
            physx::PxRigidBodyExt::updateMassAndInertia(*rigidBody.rigidBody, 10.0f);
            physicsSystem.AddPhysicsObjects(rigidBody.rigidBody);
            shape->release();
        }

        static Components::RigidBody& AddRigidBody(Graphics::Scene &scene, entt::entity entity){
            if (!connected)
                ConnectCallbacks(scene);
            return scene.getRegistry()->emplace<Components::RigidBody>(entity);
        }

        static void SetSphereDimensions(Components::RigidBody& sphereCollider, float radius){
            sphereCollider.radius = radius;
        }

        static void SetBoxDimensions(Components::RigidBody& boxCollider, glm::vec3 dimensions){
            boxCollider.dimensions = physx::PxVec3(dimensions.x, dimensions.y, dimensions.z);
        }

        static void SetCapsuleDimensions(Components::RigidBody& capsuleCollider, float radius, float halfHeight){
            capsuleCollider.radius = radius;
            capsuleCollider.halfHeight = halfHeight;
        }

    private:
        inline static bool connected = false;

        static void ConnectCallbacks(Graphics::Scene &scene){
            scene.getRegistry()->on_construct<Components::RigidBody>().connect<&SetUpRigidBody>();
            connected = true;
        }
    };
}

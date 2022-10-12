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

            Components::Shapes::Sphere sphere;
            Components::Shapes::Box box;
            Components::Shapes::Capsule capsule;

            switch (rigidBody.shape) {
                case Components::Shapes::sphere:
                    sphere = std::get<Components::Shapes::sphere>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxSphereGeometry(sphere.radius)
                            , *mMaterial);
                    break;
                case Components::Shapes::box:
                    box = std::get<Components::Shapes::box>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxBoxGeometry(box.dimensions.x, box.dimensions.y, box.dimensions.z)
                            , *mMaterial);
                    break;
                case Components::Shapes::capsule:
                    capsule = std::get<Components::Shapes::capsule>(rigidBody.shapeInfo);
                    shape = physicsContext->createShape(
                            physx::PxCapsuleGeometry(capsule.radius, capsule.halfHeight), *mMaterial);
                    break;
            }

            auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);
            auto rotation = Graphics::Utils::TransformUtils::GetQuatRotation(transform);

            physx::PxTransform currentColliderTransform(translation.x, translation.y, translation.z,
                                                        physx::PxQuat(rotation.x, rotation.y, rotation.z, rotation.w));

            rigidBody.rigidBody = physicsContext->createRigidDynamic(currentColliderTransform);
            rigidBody.rigidBody->attachShape(*shape);
            physx::PxRigidBodyExt::updateMassAndInertia(*rigidBody.rigidBody, 10.0f);
            physicsSystem.AddPhysicsObjects(rigidBody.rigidBody);
            shape->release();
            rigidBody.rigidBody->setMass(rigidBody.mass);
        }

        static void SetUpRigidStatic(entt::registry &registry, entt::entity entity){

            auto& rigidBody = registry.get<Components::RigidStatic>(entity);
            auto& transform = registry.get<Graphics::Components::Transform>(entity);

            auto& physicsSystem = PhysicsSystem::GetPhysicsSystem();
            auto physicsContext = physicsSystem.GetPhysics();

            auto mMaterial =
                    physicsContext->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);

            physx::PxShape* shape = physicsContext->createShape(physx::PxPlaneGeometry(), *mMaterial);

            auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);
            auto rotation = Graphics::Utils::TransformUtils::GetQuatRotation(transform);

            physx::PxTransform currentColliderTransform(translation.x, translation.y, translation.z,
                                                        physx::PxQuat(rotation.x, rotation.y, rotation.z, rotation.w));

            rigidBody.rigidStatic = physicsContext->createRigidStatic(currentColliderTransform);
            rigidBody.rigidStatic->attachShape(*shape);
            physicsSystem.AddPhysicsObjects(rigidBody.rigidStatic);
            shape->release();
        }

        static Components::RigidBody& AddRigidBody(Graphics::Scene &scene, entt::entity entity){
            if (!connected)
                ConnectCallbacks(scene);
            return scene.getRegistry()->emplace<Components::RigidBody>(entity);
        }

        static Components::RigidStatic& AddRigidStatic(Graphics::Scene &scene, entt::entity entity){
            if (!connected)
                ConnectCallbacks(scene);
            return scene.getRegistry()->emplace<Components::RigidStatic>(entity);
        }

        static void AddForce(Components::RigidBody &rigidBody, glm::vec3 forceVector){
            rigidBody.rigidBody->addForce(physx::PxVec3(forceVector.x, forceVector.y, forceVector.z));
        }

        static void AddTorque(Components::RigidBody &rigidBody, glm::vec3 torqueVector){
            rigidBody.rigidBody->addTorque(physx::PxVec3(torqueVector.x, torqueVector.y, torqueVector.z));
        }

        static void SetMassProperty(Components::RigidBody &rigidBody, int mass){
            rigidBody.mass = mass;
            rigidBody.rigidBody->setMass(mass);
        }

        static void SetMaterialProperties(Components::RigidBody &rigidBody, glm::vec3 matProperties){
            rigidBody.materialProperties = physx::PxVec3(matProperties.x, matProperties.y, matProperties.z);
            UpdateShapeParameters(rigidBody);
        }

        static void SetShapeProperties(Components::RigidBody &rigidBody, struct Components::Shapes::Sphere sphere){
            rigidBody.shape = Components::Shapes::sphere;
            rigidBody.shapeInfo = sphere;
            UpdateShapeParameters(rigidBody);
        }

        static void SetShapeProperties(Components::RigidBody &rigidBody, Components::Shapes::Box box){
            rigidBody.shape = Components::Shapes::box;
            rigidBody.shapeInfo = box;
            UpdateShapeParameters(rigidBody);
        }

        static void SetShapeProperties(Components::RigidBody &rigidBody, Components::Shapes::Capsule capsule){
            rigidBody.shape = Components::Shapes::capsule;
            rigidBody.shapeInfo = capsule;
            UpdateShapeParameters(rigidBody);
        }

    private:
        inline static bool connected = false;

        static void ConnectCallbacks(Graphics::Scene &scene){
            scene.getRegistry()->on_construct<Components::RigidBody>().connect<&SetUpRigidBody>();
            scene.getRegistry()->on_construct<Components::RigidStatic>().connect<&SetUpRigidStatic>();
            connected = true;
        }

        static void UpdateShapeParameters(Components::RigidBody &rigidBody){
            auto& physicsSystem = PhysicsSystem::GetPhysicsSystem();
            auto physicsContext = physicsSystem.GetPhysics();

            UpdateShapeParameters(rigidBody,physicsContext);
        }

        static void UpdateShapeParameters(Components::RigidBody &rigidBody, physx::PxPhysics* physicsContext){
            auto mMaterial =
                    physicsContext->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);

            physx::PxShape* newShape;

            Components::Shapes::Sphere sphere;
            Components::Shapes::Box box;
            Components::Shapes::Capsule capsule;

            switch (rigidBody.shape) {
                case Components::Shapes::sphere:
                    sphere = std::get<Components::Shapes::sphere>(rigidBody.shapeInfo);
                    newShape = physicsContext->createShape(
                            physx::PxSphereGeometry(sphere.radius)
                            , *mMaterial);
                    break;
                case Components::Shapes::box:
                    box = std::get<Components::Shapes::box>(rigidBody.shapeInfo);
                    newShape = physicsContext->createShape(
                            physx::PxBoxGeometry(box.dimensions.x, box.dimensions.y, box.dimensions.z)
                            , *mMaterial);
                    break;
                case Components::Shapes::capsule:
                    capsule = std::get<Components::Shapes::capsule>(rigidBody.shapeInfo);
                    newShape = physicsContext->createShape(
                            physx::PxCapsuleGeometry(capsule.radius, capsule.halfHeight), *mMaterial);
                    break;
                case Components::Shapes::plane:
                    newShape = physicsContext->createShape(physx::PxPlaneGeometry(), *mMaterial);
                    break;
            }

            rigidBody.rigidBody->attachShape(*newShape);
        }
    };
}

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
            std::cout<<"On Connect worked"<<std::endl;

            auto& rigidBody = registry.get<Components::SphereCollider>(entity);
            auto& transform = registry.get<Graphics::Components::Transform>(entity);

            auto& physicsSystem = PhysicsSystem::GetPhysicsSystem();
            auto physicsContext = physicsSystem.GetPhysics();

            auto mMaterial =
                    physicsContext->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);
            auto shape = physicsContext->createShape(physx::PxSphereGeometry(rigidBody.radius), *mMaterial);

            auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

            physx::PxTransform currentColliderTransform(physx::PxVec3(translation.x, translation.y, translation.z));
            rigidBody.rigidBody = physicsContext->createRigidDynamic(currentColliderTransform);
            rigidBody.rigidBody->attachShape(*shape);
            physx::PxRigidBodyExt::updateMassAndInertia(*rigidBody.rigidBody, 10.0f);
            physicsSystem.AddPhysicsObjects(rigidBody.rigidBody);
            shape->release();

            /*physx::PxPhysics* mPhysics = scene.GetPhysicsBase();
            physx::PxScene* mScene = scene.GetPhysicsScene();

            auto registry = scene.getRegistry();
            auto sphereView = registry->view<Components::SphereCollider, Graphics::Components::Transform>();

            for(auto& entity : sphereView) {
                auto& rigidBody = sphereView.get<Components::SphereCollider>(entity);
                auto& transform = sphereView.get<Graphics::Components::Transform>(entity);

                auto mMaterial =
                        mPhysics->createMaterial(
                                rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                                rigidBody.materialProperties.z);
                auto shape = mPhysics->createShape(physx::PxSphereGeometry(rigidBody.radius), *mMaterial);

                auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

                physx::PxTransform currentColliderTransform(physx::PxVec3(translation.x, translation.y, translation.z));
                rigidBody.rigidBody = mPhysics->createRigidDynamic(currentColliderTransform);
                rigidBody.rigidBody->attachShape(*shape);
                mScene->addActor(*rigidBody.rigidBody);
                shape->release();
            }

            auto boxView = registry->view<Components::BoxCollider, Graphics::Components::Transform>();

            for(auto& entity : boxView) {
                auto& rigidBody = boxView.get<Components::BoxCollider>(entity);
                auto& transform = boxView.get<Graphics::Components::Transform>(entity);
                auto mMaterial =
                        mPhysics->createMaterial(
                                rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                                rigidBody.materialProperties.z);
                auto shape = mPhysics->createShape(
                        physx::PxBoxGeometry(rigidBody.dimensions.x, rigidBody.dimensions.y, rigidBody.dimensions.z)
                        , *mMaterial);

                auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

                physx::PxTransform localTm(physx::PxVec3(translation.x, translation.y, translation.z));
                rigidBody.rigidBody = mPhysics->createRigidDynamic(localTm);
                rigidBody.rigidBody->attachShape(*shape);
                mScene->addActor(*rigidBody.rigidBody);
                shape->release();
            }

            auto capsuleView = registry->view<Components::CapsuleCollider, Graphics::Components::Transform>();

            for(auto& entity : capsuleView) {
                auto& rigidBody = capsuleView.get<Components::CapsuleCollider>(entity);
                auto& transform = capsuleView.get<Graphics::Components::Transform>(entity);
                auto mMaterial =
                        mPhysics->createMaterial(
                                rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                                rigidBody.materialProperties.z);
                auto shape = mPhysics->createShape(
                        physx::PxCapsuleGeometry(rigidBody.radius, rigidBody.halfHeight), *mMaterial);

                auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

                physx::PxTransform localTm(physx::PxVec3(translation.x, translation.y, translation.z));
                rigidBody.rigidBody = mPhysics->createRigidDynamic(localTm);
                rigidBody.rigidBody->attachShape(*shape);
                mScene->addActor(*rigidBody.rigidBody);
                shape->release();
            }

            auto planeView = registry->view<Components::PlaneCollider, Graphics::Components::Transform>();

            for(auto& entity : planeView) {
                auto& rigidBody = planeView.get<Components::PlaneCollider>(entity);
                auto& transform = planeView.get<Graphics::Components::Transform>(entity);
                auto mMaterial =
                        mPhysics->createMaterial(
                                rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                                rigidBody.materialProperties.z);
                auto shape = mPhysics->createShape(physx::PxPlaneGeometry(), *mMaterial);

                auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

                physx::PxTransform localTm(physx::PxVec3(translation.x, translation.y, translation.z));
                rigidBody.rigidBody = mPhysics->createRigidDynamic(localTm);
                rigidBody.rigidBody->attachShape(*shape);
                mScene->addActor(*rigidBody.rigidBody);
                shape->release();
            }*/
        }

        static Components::SphereCollider& AddRigidBody(Graphics::Scene &scene, entt::entity entity){
            if (!connected)
                ConnectCallbacks(scene);
            return scene.getRegistry()->emplace<Components::SphereCollider>(entity);
        }

        static void SetSphereDimensions(Components::SphereCollider& sphereCollider, float radius){
            sphereCollider.radius = radius;
        }

        static void SetBoxDimensions(Components::BoxCollider& boxCollider, glm::vec3 dimensions){
            boxCollider.dimensions = physx::PxVec3(dimensions.x, dimensions.y, dimensions.z);
        }

        static void SetCapsuleDimensions(Components::CapsuleCollider& capsuleCollider, float radius, float halfHeight){
            capsuleCollider.radius = radius;
            capsuleCollider.halfHeight = halfHeight;
        }

    private:
        inline static bool connected = false;

        static void ConnectCallbacks(Graphics::Scene &scene){
            scene.getRegistry()->on_construct<Components::SphereCollider>().connect<&SetUpRigidBody>();
            connected = true;
        }
    };
}

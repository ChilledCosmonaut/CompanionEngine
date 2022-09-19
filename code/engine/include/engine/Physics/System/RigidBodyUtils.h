#pragma once

#include "PxPhysicsAPI.h"

#include "engine/Physics/Components/RigidBody.h"
#include "engine/GraphicsEngine/Components/Transform.h"
#include "engine/GraphicsEngine/Scene.h"
#include "engine/Time.h"

namespace gl3::engine::Physics::Utils {

    class RigidBodyUtils {
    public:
        static void SetUpRigidBody(Graphics::Scene& scene){
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

        static void UpdatePhysics(Graphics::Scene& scene){
            /*physx::PxScene* mScene = scene.GetPhysicsScene();

            mScene->simulate(Time::GetDeltaTime());
            mScene->fetchResults(true);*/
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
    };
}

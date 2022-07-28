#pragma once

#include "PxPhysicsAPI.h"

#include "engine/Physics/Components/RigidBody.h"
#include "engine/GraphicsEngine/Components/Transform.h"
#include "engine/GraphicsEngine/Scene.h"

namespace gl3::engine::Physics::Utils {

    class RigidBodyUtils {
    public:
        static void SetUpRigidBody(Graphics::Scene& scene){
            auto registry = scene.getRegistry();
            auto componentView = registry->view<Components::RigidBody, Graphics::Components::Transform>();
            physx::PxPhysics* mPhysics = scene.GetPhysicsBase();
            physx::PxScene* mScene = scene.GetPhysicsScene();

            for(auto& entity : componentView) {
                auto& rigidBody = componentView.get<Components::RigidBody>(entity);
                auto& transform = componentView.get<Graphics::Components::Transform>(entity);
                auto mMaterial =
                        mPhysics->createMaterial(
                                rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                                rigidBody.materialProperties.z);
                auto shape = mPhysics->createShape(physx::PxSphereGeometry(rigidBody.shape), *mMaterial);

                auto translation = Graphics::Utils::TransformUtils::GetTranslation(transform);

                physx::PxTransform localTm(physx::PxVec3(translation.x, translation.y, translation.z));
                physx::PxRigidDynamic* body = mPhysics->createRigidDynamic(localTm);
                body->attachShape(*shape);
                mScene->addActor(*body);
                shape->release();
            }
        }

        static void SetDimensions(Components::RigidBody& rigidBody, float x, float y, float z){
            rigidBody.shapeDimensions = physx::PxVec3(x, y, z);
        }
    };
}

#include "PhysicsSystem.h"

namespace gl3::engine::Physics {

    PhysicsSystem *PhysicsSystem::GetPhysicsSystem() {
        if (physicsSystem == nullptr)
            physicsSystem = new PhysicsSystem();
        return physicsSystem;
    }

    void PhysicsSystem::DestroyPhysicsSystem() {
        physicsSystem->~PhysicsSystem();
        physicsSystem = nullptr;
    }

    void PhysicsSystem::SetUp() {

        auto &registry = Ecs::Registry::getCurrent();

        auto initRigidBodies = registry.view<RigidBody, Graphics::Transform, Ecs::Flags::Setup<RigidBody>>();

        for (auto entity: initRigidBodies) {
            auto &rigidBody = registry.get<RigidBody>(entity);
            auto &transform = registry.get<Graphics::Transform>(entity);

            auto mMaterial =
                    mPhysics->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);

            physx::PxShape *shape = std::visit(
                    [this, &mMaterial](auto&& x) -> physx::PxShape* {
                            return CreateShape(x, mMaterial);
                        }, rigidBody.shapeInfo);

            physx::PxTransform currentColliderTransform(transform.translation.x, transform.translation.y, transform.translation.z,
                                                        physx::PxQuat(
                                                                transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w));

            rigidBody.rigidBody = mPhysics->createRigidDynamic(currentColliderTransform);
            rigidBody.rigidBody->attachShape(*shape);
            physx::PxRigidBodyExt::updateMassAndInertia(*rigidBody.rigidBody, 10.0f);
            mScene->addActor(*rigidBody.rigidBody);
            shape->release();
            rigidBody.rigidBody->setMass(rigidBody.mass);

            Ecs::Registry::RemoveSetupFlag<RigidBody>(entity);
        }

        auto initRigidStatics = registry.view<RigidStatic, Graphics::Transform, Ecs::Flags::Setup<RigidStatic>>();

        for (auto entity: initRigidStatics) {
            auto &rigidStatic = registry.get<RigidStatic>(entity);
            auto &transform = registry.get<Graphics::Transform>(entity);

            auto mMaterial =
                    mPhysics->createMaterial(
                            rigidStatic.materialProperties.x, rigidStatic.materialProperties.y,
                            rigidStatic.materialProperties.z);

            physx::PxShape *shape = mPhysics->createShape(physx::PxPlaneGeometry(), *mMaterial);

            physx::PxTransform currentColliderTransform(transform.translation.x, transform.translation.y, transform.translation.z,
                                                        physx::PxQuat(transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w));

            rigidStatic.rigidStatic = mPhysics->createRigidStatic(currentColliderTransform);
            rigidStatic.rigidStatic->attachShape(*shape);
            mScene->addActor(*rigidStatic.rigidStatic);
            shape->release();

            Ecs::Registry::RemoveSetupFlag<RigidStatic>(entity);
        }

    }

    void PhysicsSystem::Update() {

        auto &registry = Ecs::Registry::getCurrent();

        auto updatedRigidBodies = registry.view<RigidBody, Ecs::Flags::Update<RigidBody>>();

        for (auto &entity: updatedRigidBodies) {
            auto &rigidBody = updatedRigidBodies.get<RigidBody>(entity);

            //ToDo: Update rigid bodies here when values have been changed
            auto mMaterial =
                    mPhysics->createMaterial(
                            rigidBody.materialProperties.x, rigidBody.materialProperties.y,
                            rigidBody.materialProperties.z);

            physx::PxShape *newShape = std::visit(
                    [this, &mMaterial](auto&& x) -> physx::PxShape* {
                        return CreateShape(x, mMaterial);
                    }, rigidBody.shapeInfo);

            rigidBody.rigidBody->attachShape(*newShape);

            rigidBody.rigidBody->setMass(rigidBody.mass);

            Ecs::Registry::RemoveUpdateFlag<RigidBody>(entity);
        }

        //For this to work use two Transform update cycles
        auto updatedBodyTransforms = registry.view<RigidBody, Graphics::Transform, Ecs::Flags::Update<Graphics::Transform>>();

        for (auto &entity: updatedBodyTransforms) {
            auto &rigidBody = updatedBodyTransforms.get<RigidBody>(entity);
            auto &transform = registry.get<Graphics::Transform>(entity);

            physx::PxTransform updatedTransform(transform.translation.x, transform.translation.y, transform.translation.z,
                                                physx::PxQuat(transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w));

            rigidBody.rigidBody->setGlobalPose(updatedTransform);
        }

        auto updatedStaticTransforms = registry.view<RigidStatic, Graphics::Transform, Ecs::Flags::Update<Graphics::Transform>>();

        for (auto &entity: updatedStaticTransforms) {
            auto &rigidBody = updatedStaticTransforms.get<RigidStatic>(entity);
            auto &transform = registry.get<Graphics::Transform>(entity);

            physx::PxTransform updatedTransform(transform.translation.x, transform.translation.y, transform.translation.z,
                                                physx::PxQuat(transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w));

            rigidBody.rigidStatic->setGlobalPose(updatedTransform);
        }

        mScene->simulate(Time::GetDeltaTime());
        mScene->fetchResults(true);

        auto componentView = registry.view<RigidBody, Graphics::Transform>();

        for (auto &entity: componentView) {
            auto &rigidBody = componentView.get<RigidBody>(entity);
            auto &transform = componentView.get<Graphics::Transform>(entity);

            auto physicsTransform = rigidBody.rigidBody->getGlobalPose();

            Graphics::TransformationUtils::SetRotation(entity, transform, glm::quat(
                    physicsTransform.q.w, physicsTransform.q.x, physicsTransform.q.y, physicsTransform.q.z));
            Graphics::TransformationUtils::SetTranslation(entity, transform, glm::vec3(
                    physicsTransform.p.x, physicsTransform.p.y, physicsTransform.p.z));

            Ecs::Registry::UpdateComponent<Graphics::Transform>(entity);
        }
    }

    void PhysicsSystem::Shutdown() {

        auto &registry = Ecs::Registry::getCurrent();

        auto shutdownRigidBodies = registry.view<RigidBody, Ecs::Flags::Destroy<RigidBody>>();

        for (auto entity: shutdownRigidBodies) {
            auto &rigidStatic = registry.get<RigidBody>(entity);

            rigidStatic.rigidBody->release();

            Ecs::Registry::RemoveDestroyFlag<RigidBody>(entity);
        }

        auto shutdownRigidStatics = registry.view<RigidStatic, Ecs::Flags::Destroy<RigidStatic>>();

        for (auto entity: shutdownRigidStatics) {
            auto &rigidStatic = registry.get<RigidStatic>(entity);

            rigidStatic.rigidStatic->release();

            Ecs::Registry::RemoveDestroyFlag<RigidStatic>(entity);
        }
    }

    PhysicsSystem::PhysicsSystem() {
        // init physx
        mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
        if (!mFoundation) throw ("PxCreateFoundation failed!");

        mToleranceScale.length = 100;        // typical length of an object
        mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice

#if DEBUG
        mPvd = PxCreatePvd(*mFoundation);
        physx::PxPvdTransport *transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
        mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
#else
        mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale);
#endif

        physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
        sceneDesc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);
        mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
        sceneDesc.cpuDispatcher = mDispatcher;
        sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
        mScene = mPhysics->createScene(sceneDesc);

#if DEBUG
        physx::PxPvdSceneClient *pvdClient = mScene->getScenePvdClient();
        if (pvdClient) {
            pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
            pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
            pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
        }
#endif
        physicsSystem = this;
    }

    PhysicsSystem::~PhysicsSystem() {

        mPhysics->release();
#if DEBUG
        mPvd->release();
        mPvdTransporter->release();
#endif
        mFoundation->release();
    }

    physx::PxShape *PhysicsSystem::CreateShape(Shapes::Sphere &sphere, physx::PxMaterial* material) {
        return mPhysics->createShape(physx::PxSphereGeometry(sphere.radius), *material);
    }

    physx::PxShape *PhysicsSystem::CreateShape(Shapes::Box &box, physx::PxMaterial* material) {
        return mPhysics->createShape(physx::PxBoxGeometry(box.dimensions.x, box.dimensions.y, box.dimensions.z), *material);
    }

    physx::PxShape *PhysicsSystem::CreateShape(Shapes::Capsule &capsule, physx::PxMaterial* material) {
        return mPhysics->createShape(physx::PxCapsuleGeometry(capsule.radius, capsule.halfHeight), *material);
    }
}

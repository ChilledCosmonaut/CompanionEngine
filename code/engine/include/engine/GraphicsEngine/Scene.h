#pragma once

#include "PxConfig.h" //Needs to stay here else PhysX will not find some HeaderFiles
#include <memory>
#include <utility>
#include "../../../src/EntityComponentSystem/entt.hpp"
#include "engine/GraphicsEngine/Components/Skybox.h"
#include "engine/GraphicsEngine/Components/Model.h"
#include "engine/GraphicsEngine/Components/Camera.h"
#include "engine/GraphicsEngine/Utils/TransformUtils.h"
#include "engine/Physics/PhysicsScene.h"

namespace gl3::engine::Graphics{

    class Scene {

    public:

        entt::registry* getRegistry(){
            return &registry;
        }

        template<typename Included, typename Excluded>
        entt::basic_view<entt::entity, entt::get_t<Included>, entt::exclude_t<Excluded>> getAllComponents(){
            return registry.view<Included, Excluded>();
        }

        void setMainCamera(entt::entity newMainCameraObject){
            mainCameraObject = newMainCameraObject;
        }

        entt::entity getMainCamera(){
            return mainCameraObject;
        }

        physx::PxScene* GetPhysicsScene(){
            return physicsScene.GetScene();
        }

        physx::PxPhysics* GetPhysicsBase(){
            return physicsScene.GetPhysicsBase();
        }

        virtual void onSetup() = 0;

    protected:

        void AddSkybox(){
            entt::entity entity = CreateEntity();
            registry.emplace<Components::SkyboxComponent>(entity);
        }

        void AddMainCamera(){
            entt::entity entity = CreateEntity();
            registry.emplace<Components::CameraComponent>(entity);
            mainCameraObject = entity;
        }

        entt::entity CreateEntity(){
            entt::entity entity = registry.create();
            auto &transform = registry.emplace<Components::Transform>(entity);
            engine::Graphics::Utils::TransformUtils::SetCurrentRegistry(transform, registry);
            return entity;
        }

        //template<typename component>
        /*void AddModel(entt::entity entity, std::string path){
            Components::Model model = registry.emplace<Components::Model>(entity);
            model.path = std::move(path);
        }*/

        entt::registry registry;
        entt::entity mainCameraObject;
        Physics::PhysicsScene physicsScene {};
    };
}
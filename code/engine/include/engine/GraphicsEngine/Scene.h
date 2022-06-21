#pragma once

#include <memory>
#include <utility>
#include "../../../src/EntityComponentSystem/entt.hpp"
#include "engine/EntityComponentSystem/Entity.h"
#include "engine/GraphicsEngine/Components/Skybox.h"
#include "engine/GraphicsEngine/Components/Model.h"
#include "engine/GraphicsEngine/Components/Camera.h"

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

        virtual void onSetup() = 0;

    protected:

        void AddSkybox(){
            entt::entity entity = registry.create();
            registry.emplace<Components::SkyboxComponent>(entity);
        }

        void AddMainCamera(){
            entt::entity entity = registry.create();
            registry.emplace<Components::CameraComponent>(entity);
            registry.emplace<Components::Transform>(entity);
            mainCameraObject = entity;
        }

        entt::entity CreateEntity(){
            entt::entity newEntity = registry.create();
            registry.emplace<Components::Transform>(newEntity);
            return newEntity;
        }

        //template<typename component>
        void AddModel(entt::entity entity, std::string path){
            Components::Model model = registry.emplace<Components::Model>(entity);
            model.path = std::move(path);
        }

        entt::registry registry;
        entt::entity mainCameraObject;
    };
}
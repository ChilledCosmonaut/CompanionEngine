#pragma once

#include "engine/Events.h"
#include "engine/Context.h"
#include "Scene.h"
#include "engine/Systems/Physics/PhysicsSystem.h"
#include "../../src/Systems/Graphics/GraphicsSystem.h"
#include "engine/Systems/Sound/AudioSystem.h"

namespace gl3::engine {
    class Game {

    public:
        using event_t = events::Event<Game, Game&>;

        event_t onSetup;
        event_t onUpdate;
        event_t onDestroy;

        Game(int width, int height, const std::string &title, Scene* startScene = nullptr);
        virtual ~Game();

        void run();

        GLFWwindow *getWindow() { return context.getWindow(); }

        void ChangeActiveSceneTo(Scene* scene){
            currentScene = scene;
            currentScene->onSetup();
            graphicsSystem.SetUpScene(*currentScene);
        }

        Scene *getCurrentScene() {
            return currentScene;
        }

    private:

        void SetUpEngineSystems();
        void UpdateEngineSystems();
        void DestroyEngineSystems();

        context::Context context;
        Scene* currentScene;
        Physics::PhysicsSystem physicsSystem;
        Graphics::Systems::GraphicsSystem graphicsSystem;
        soundSystem::AudioSystem& audioSystem;
    };
}
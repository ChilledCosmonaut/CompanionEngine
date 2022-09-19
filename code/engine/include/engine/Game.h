#pragma once

#include "engine/Events.h"
#include "engine/Context.h"
#include "engine/Systems/Graphics/Scene.h"
#include "engine/Systems/Physics/PhysicsSystem.h"
#include "../../src/Systems/Graphics/GraphicsSystem.h"

namespace gl3::engine {
    class Game {

    public:
        using event_t = events::Event<Game, Game&>;
        using event_render = events::Event<Game, Graphics::Scene&>;

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_render onDrawCall;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        event_render onSwitchingScenes;

        Game(int width, int height, const std::string &title, Graphics::Scene* startScene = nullptr);
        virtual ~Game();

        void run();

        GLFWwindow *getWindow() { return context.getWindow(); }

        void ChangeActiveSceneTo(Graphics::Scene* scene){
            currentScene = scene;
            currentScene->onSetup();
            graphicsSystem.SetUpScene(*currentScene);
            onSwitchingScenes.invoke(*currentScene);
        }

        Graphics::Scene *getCurrentScene() {
            return currentScene;
        }

    protected:
        void start() {};
        virtual void update(GLFWwindow *window) {}
        void draw();

    private:
        context::Context context;
        Graphics::Scene* currentScene;
        Physics::PhysicsSystem physicsSystem;
        Graphics::Systems::GraphicsSystem graphicsSystem;
    };
}
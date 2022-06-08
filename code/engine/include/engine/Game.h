#pragma once
#include "engine/Events.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <soloud.h>
#include <soloud_wav.h>
#include "engine/Context.h"
#include "engine/GraphicsEngine/Scene.h"
#include "engine/GraphicsEngine/Systems/GraphicsSystem.h"

class GraphicsSystem;
namespace gl3::engine {
    class Game {

    public:
        using event_t = events::Event<Game, Game&>;

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        Game(int width, int height, const std::string &title, Graphics::Scene* startScene = nullptr);
        virtual ~Game();

        void run();
        GLFWwindow *getWindow() { return context.getWindow(); }
        void ChangeActiveSceneTo(Graphics::Scene* scene){
            currentScene = scene;
            currentScene->onSetup();
            graphicsSystem.Start(*currentScene);
        }

        Graphics::Scene *getCurrentScene() {
            return currentScene;
        }

    protected:
        void start() {}
        virtual void update(GLFWwindow *window) {}
        void draw();

    private:
        context::Context context;
        Graphics::Scene* currentScene;
        Graphics::Systems::GraphicsSystem graphicsSystem {};
    };
}
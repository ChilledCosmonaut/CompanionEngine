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
#include "engine/EntityComponentSystem/EntityManager.h"

namespace gl3::engine {
    class Game {
        using event_t = events::Event<Game, Game&>;

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        void run();
        GLFWwindow *getWindow() { return context.getWindow(); }

        entityComponentSystem::EntityManager entityManager;
        entityComponentSystem::ComponentManager componentManager;

    protected:
        Game(int width, int height, const std::string &title);
        virtual void start() {}
        virtual void update(GLFWwindow *window) {}
        virtual void draw() {}
        virtual ~Game();

        SoLoud::Soloud audio;

    private:
        context::Context context;
    };
}
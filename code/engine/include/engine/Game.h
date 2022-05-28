#pragma once
#include "engine/Events.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <soloud.h>
#include <soloud_wav.h>
//#include "engine/Context.h"
#include "engine/EntityComponentSystem/EntityManager.h"

namespace gl3::engine {
    class Game {
        using event_t = events::Event<Game, Game&>;

        void run();
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
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
        float deltaTime = 1.0f / 60;

    private:
        void updateDeltaTime();

        context::Context context;
        float lastFrameTime = 1.0f / 60;
    };
}
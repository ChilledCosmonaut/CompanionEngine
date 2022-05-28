#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/Game.h"

namespace gl3::engine {
    using Context = engine::context::Context;

    Game::Game(int width, int height, const std::string &title) :
            context(width, height, title),
            componentManager(*this),
            entityManager(componentManager, *this) {
        audio.init();
        audio.setGlobalVolume(0.1f);
    }

    void Game::run() {
        onStartup.invoke(*this);
        start();
        onAfterStartup.invoke(*this);
        context.run([&](Context &ctx){
            onBeforeUpdate.invoke(*this);
            update(getWindow());
            draw();
            updateDeltaTime();
            onAfterUpdate.invoke(*this);
        });
        onBeforeShutdown.invoke(*this);
        onShutdown.invoke(*this);
    }

    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    glm::mat4 Game::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0),
                                     glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f / 600.0f, 0.1f, 100.0f);

        return projection * view * model;
    }

    Game::~Game() {
        context.~Context();
    }
}
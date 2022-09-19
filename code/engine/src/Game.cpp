#include "engine/Game.h"

namespace gl3::engine {
    using Context = engine::context::Context;

    Game::Game(int width, int height, const std::string &title, Graphics::Scene* startScene):
            context(width, height, title),
            currentScene(startScene),
            physicsSystem(){
        glEnable(GL_DEPTH_TEST);
    }

    void Game::run() {
        onStartup.invoke(*this);
        start();
        onAfterStartup.invoke(*this);
        context.run([&](Context &ctx){
            onBeforeUpdate.invoke(*this);
            update(getWindow());
            draw();
            Time::updateDeltaTime();
            onAfterUpdate.invoke(*this);
        });
        onBeforeShutdown.invoke(*this);
        onShutdown.invoke(*this);
    }

    void Game::draw() {
        if (currentScene != nullptr) {
            onDrawCall.invoke(*currentScene);
        }
    }

    Game::~Game() {
        context.~Context();
    }
}
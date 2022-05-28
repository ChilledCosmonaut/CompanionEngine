#include <stdexcept>
#include "engine/Game.h"
#include "engine/Time.h"

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
            Time::updateDeltaTime();
            onAfterUpdate.invoke(*this);
        });
        onBeforeShutdown.invoke(*this);
        onShutdown.invoke(*this);
    }

    Game::~Game() {
        context.~Context();
    }
}
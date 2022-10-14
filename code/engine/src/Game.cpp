#include "engine/Game.h"

namespace gl3::engine {
    using Context = engine::context::Context;

    Game::Game(int width, int height, const std::string &title, Scene* startScene):
            context(width, height, title),
            currentScene(startScene),
            physicsSystem(),
            graphicsSystem() {
        glEnable(GL_DEPTH_TEST);
        audioSystem = soundSystem::AudioSystem::GetAudioSystem();
    }

    void Game::run() {
        SetUpEngineSystems();
        onSetup.invoke(*this);
        context.run([&](Context &ctx){
            onDestroy.invoke(*this);
            onSetup.invoke(*this);
            onUpdate.invoke(*this);
            UpdateEngineSystems();
            Time::updateDeltaTime();
        });
        onDestroy.invoke(*this);
        DestroyEngineSystems();
    }

    Game::~Game() {
        audioSystem.~AudioSystem();
        physicsSystem.~PhysicsSystem();
        context.~Context();
    }

    void Game::SetUpEngineSystems() {
        audioSystem.SetupAudio();
    }

    void Game::UpdateEngineSystems() {
        physicsSystem.SimulatePhysics(*currentScene);
        audioSystem.UpdateAudio();
        graphicsSystem.DrawScene(*currentScene);
    }

    void Game::DestroyEngineSystems() {
        audioSystem.DestroyAudio();
    }
}
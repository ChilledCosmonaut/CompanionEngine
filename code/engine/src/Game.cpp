#include "engine/Game.h"

namespace gl3::engine {
    using Context = engine::context::Context;

    Game::Game(int width, int height, const std::string &title, Scene* startScene):
            context(width, height, title),
            currentScene(startScene) {
        glEnable(GL_DEPTH_TEST);
        graphicsSystem = Graphics::Systems::GraphicsSystem::GetGraphicsSystem();
        physicsSystem = Physics::PhysicsSystem::GetPhysicsSystem();
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
        DestroyEngineSystems();
    }

    void Game::SetUpEngineSystems() {
        audioSystem->SetupAudio();
        graphicsSystem->SetUp();
        physicsSystem->SetUp();
    }

    void Game::UpdateEngineSystems() {
        physicsSystem->Update();
        audioSystem->UpdateAudio();
        graphicsSystem->Update();
    }

    void Game::DestroyEngineSystems() {
        audioSystem->DestroyAudio();
        physicsSystem->DestroyPhysicsSystem();
        graphicsSystem->Shutdown();
        context.~Context();
    }
}
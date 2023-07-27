#include "engine/Game.h"

namespace gl3::engine {
    using Context = engine::context::Context;

    Game::Game(int width, int height, const std::string &title, Scene* startScene):
            context(width, height, title),
            currentScene(startScene) {
        glEnable(GL_DEPTH_TEST);
        graphicsSystem = Graphics::GraphicsSystem::GetGraphicsSystem();
        physicsSystem = Physics::PhysicsSystem::GetPhysicsSystem();
        audioSystem = soundSystem::AudioSystem::GetAudioSystem();
        transformSystem = Graphics::TransformSystem::GetTransformSystem();
        inputManager = inputSystem::InputManager::GetInputManager();
        cleanUpSystem = Ecs::CleanUpSystem::GetCleanUpSystem();
    }

    void Game::run() {
        SetUpCallEngineSystems();
        onSetup.invoke(*this);
        context.run([&](Context &ctx){
            SetUpCallEngineSystems();
            onSetup.invoke(*this);
            inputManager->UpdateInput(getWindow());
            onUpdate.invoke(*this);
            UpdateCallEngineSystems();
            onDestroy.invoke(*this);
            DestroyCallEngineSystems();
            Time::updateDeltaTime();
        });
        onDestroy.invoke(*this);
        DestroyCallEngineSystems();
    }

    Game::~Game() {
        soundSystem::AudioSystem::DestroyAudioSystem();
        Physics::PhysicsSystem::DestroyPhysicsSystem();
        Graphics::GraphicsSystem::DestroyGraphicsSystem();
        context.~Context();
        Graphics::TransformSystem::DestroyTransformSystem();
        inputSystem::InputManager::DestroyInputManager();
    }

    void Game::SetUpCallEngineSystems() {
        transformSystem->SetupTransform();
        audioSystem->SetupAudio();
        graphicsSystem->SetUp();
        physicsSystem->SetUp();
    }

    void Game::UpdateCallEngineSystems() {
        transformSystem->UpdateTransform(currentScene);
        physicsSystem->Update();
        transformSystem->UpdateTransform(currentScene);
        audioSystem->UpdateAudio();
        graphicsSystem->Update();
    }

    void Game::DestroyCallEngineSystems() {
        audioSystem->DestroyAudio();
        physicsSystem->Shutdown();
        graphicsSystem->Shutdown();
        transformSystem->DestroyTransform();
        cleanUpSystem->Shutdown();
    }
}
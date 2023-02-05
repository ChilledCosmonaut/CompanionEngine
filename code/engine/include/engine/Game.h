#pragma once

#include "engine/Events.h"
#include "engine/Context.h"
#include "engine/Systems/Input/InputManager.h"
#include "Scene.h"
#include "../../src/Systems/Physics/PhysicsSystem.h"
#include "../../src/Systems/Graphics/GraphicsSystem.h"
#include "../../src/Systems/Sound/AudioSystem.h"
#include "../../src/Systems/Graphics/TransformSystem.h"
#include "../../src/ECS/CleanUpSystem.h"

namespace gl3::engine {
    /**
     * Game class abstraction. Holds all important info for the game, like scene, context, etc.
     */
    class Game {
    public:
        using event_t = events::Event<Game, Game&>;

        event_t onSetup;
        event_t onUpdate;
        event_t onDestroy;

        /**
         * Constructor for the game clas
         * @param width Screen width of game
         * @param height Screen height of game
         * @param title Name of created window
         * @param startScene Optional start scene
         */
        Game(int width, int height, const std::string &title, Scene* startScene = nullptr);
        virtual ~Game();

        /// Starts the created game instance
        void run();

        /**
         * Retrieves currently active window
         * @return Current window instance
         */
        GLFWwindow *getWindow() { return context.getWindow(); }

        /**
         * Changes active scene to the new pointed at scene
         * @param scene New scene that should be displayed
         */
        void ChangeActiveSceneTo(Scene* scene){
            currentScene = scene;
            currentScene->onSetup();
        }

        /**
         * Retrieves currently active scene
         * @return Pointer to active scene
         */
        Scene *getCurrentScene() {
            return currentScene;
        }

    private:

        void SetUpCallEngineSystems();
        void UpdateCallEngineSystems();
        void DestroyCallEngineSystems();

        context::Context context;
        Scene* currentScene;
        Physics::PhysicsSystem* physicsSystem;
        Graphics::GraphicsSystem* graphicsSystem;
        soundSystem::AudioSystem* audioSystem;
        Graphics::TransformSystem* transformSystem;
        inputSystem::InputManager* inputManager;
        Ecs::CleanUpSystem* cleanUpSystem;
    };
}
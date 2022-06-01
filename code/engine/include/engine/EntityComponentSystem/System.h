#pragma once
#include "engine/Game.h"

namespace gl3::engine::entityComponentSystem {
    class System {
        friend class Graphics::Scene;

    public:
        explicit System(Game &engine) : engine(engine) {}
        System(System &&) = delete;
        System(const System &) = delete;
        virtual ~System() = default;

    protected:
        virtual void Start(engine::Game &game) = 0;
        virtual void Update(engine::Game &game) = 0;
        virtual void OnShutdown(engine::Game &game) = 0;

        engine::Game &engine;

    private:
        void SetUpSystem(engine::Game &game){
            engine = game;
            engine.onStartup.addListener([&] (engine::Game &game){
                Start(game);
            });
            engine.onBeforeUpdate.addListener([&] (engine::Game &game){
                Update(game);
            });
            engine.onShutdown.addListener([&] (engine::Game &game){
                OnShutdown(game);
            });
        }
    };
}
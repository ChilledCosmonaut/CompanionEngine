#pragma once
#include "engine/Game.h"

namespace gl3::engine::entityComponentSystem {
    class System {

    public:
        System() = default;
        System(System &&) = delete;
        System(const System &) = delete;
        virtual ~System() = default;

        void SetUpSystem(engine::Game &game){
            game.onSetup.addListener([&] (engine::Game &game){
                OnSetUp(game);
            });
            game.onUpdate.addListener([&] (engine::Game &game){
                Update(game);
            });
            game.onDestroy.addListener([&] (engine::Game &game){
                OnShutdown(game);
            });
        }

    protected:
        virtual void OnSetUp(engine::Game &game) = 0;
        virtual void Update(engine::Game &game) = 0;
        virtual void OnShutdown(engine::Game &game) = 0;
    };
}
#pragma once
#include "engine/Game.h"

namespace gl3::engine::entityComponentSystem {
    class System {
        friend class Graphics::Scene;

    public:
        System() = default;
        System(System &&) = delete;
        System(const System &) = delete;
        virtual ~System() = default;

        void SetUpSystem(engine::Game &game){
            game.onSetup.addListener([&] (engine::Game &game){
                OnSetUp(game);
            });
            game.onBeforeUpdate.addListener([&] (engine::Game &game){
                Update(game);
            });
            game.onDestroy.addListener([&] (engine::Game &game){
                OnShutdown(game);
            });
            game.onSwitchingScenes.addListener([&] (Graphics::Scene &scene){
                OnSwitchingScenes(scene);
            });
            game.onDrawCall.addListener([&] (Graphics::Scene &scene){
                OnDrawCall(scene);
            });
        }

    protected:
        virtual void OnSetUp(engine::Game &game) = 0;
        virtual void Update(engine::Game &game) = 0;
        virtual void OnShutdown(engine::Game &game) = 0;

        virtual void OnSwitchingScenes(Graphics::Scene &scene) = 0;
        virtual void OnDrawCall(Graphics::Scene &scene) = 0;
    };
}
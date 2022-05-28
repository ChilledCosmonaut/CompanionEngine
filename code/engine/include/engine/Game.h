#pragma once
#include "engine/Events.h"

namespace gl3::engine {
    class Game {
        using event_t = events::Event<Game, Game&>;

        void run();

    };
}
#pragma once

#include "engine/Systems/Input/InputGroup.h"

namespace game::controls {
    using namespace gl3::engine::inputSystem;

    class SpaceShipControls : InputGroup {

        void UpdateKeys();
    };
}
#pragma once

namespace gl3::game {

    struct FighterBehaviour {
        float lifePoints = 100;

        float maxSpeed = 5;
    };

    struct CarrierBehaviour {
        float lifePoints = 300;

        float maxSpeed = 2.5f;
    };
}

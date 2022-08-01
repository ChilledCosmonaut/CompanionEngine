#pragma once

namespace gl3::game {

    struct PlayerProjectile {
        float lifetime = 0;
        float damage = 10;
    };

    struct EnemyProjectile {
        float lifetime = 0;
        float damage = 10;
    };
}

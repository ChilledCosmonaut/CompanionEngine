#pragma once

#include "engine/ECS/System.h"
#include "engine/Systems/Physics/Utils/PhysicsUtils.h"

#include "../Components/Health.h"
#include "../Components/Laser.h"

namespace gl3::game {
    class ShootingMechanics {
    public:
        static void Shoot(const engine::Graphics::Transform &transform);
    };
}

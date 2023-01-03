#pragma once

#include "vector"

#include "engine/ECS/Registry.h"
#include "engine/Systems/Graphics/Components/DirectionLight.h"
#include "engine/Systems/Graphics/Components/PointLight.h"
#include "engine/Systems/Graphics/Components/SpotLight.h"

namespace gl3::engine::Graphics {

    class LightingSystem {
    public:
        static std::vector<DirectionLight> GetDirectionLightInfo(entt::registry& registry);

        static std::vector<std::pair<Transform, PointLight>> GetPointLightInfo(entt::registry& registry);

        static std::vector<std::pair<Transform, SpotLight>> GetSpotLightInfo(entt::registry& registry);
    };
}
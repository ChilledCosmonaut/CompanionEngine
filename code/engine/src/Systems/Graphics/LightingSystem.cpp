#include "LightingSystem.h"

namespace gl3::engine::Graphics {


    std::vector<DirectionLight> LightingSystem::GetDirectionLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<DirectionLight>();

        auto lightView = registry.view<DirectionLight>();
        for (auto &&[entity, light]: lightView.each()) lightVector.push_back(light);

        return lightVector;
    }

    std::vector<std::pair<Transform, PointLight>> LightingSystem::GetPointLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<std::pair<Transform, PointLight>>();

        auto lightView = registry.view<Transform, PointLight>();
        for (auto &&[entity, transform, light]: lightView.each()) lightVector.push_back({transform, light});

        return lightVector;
    }

    std::vector<std::pair<Transform, SpotLight>> LightingSystem::GetSpotLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<std::pair<Transform, SpotLight>>();

        auto lightView = registry.view<Transform, SpotLight>();
        for (auto &&[entity, transform, light]: lightView.each()) lightVector.push_back({transform, light});

        return lightVector;
    }
}
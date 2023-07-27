#include "LightingSystem.h"

namespace gl3::engine::Graphics {


    std::vector<std::pair<const Transform&, const DirectionLight&>> LightingSystem::GetDirectionLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<std::pair<const Transform&, const DirectionLight&>>();

        auto lightView = registry.view<const Transform, const DirectionLight>();
        for (auto &&[entity, transform, light]: lightView.each()) lightVector.push_back({transform, light});

        return lightVector;
    }

    std::vector<std::pair<const Transform&, const PointLight&>> LightingSystem::GetPointLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<std::pair<const Transform&, const PointLight&>>();

        auto lightView = registry.view<const Transform, const PointLight>();
        for (auto &&[entity, transform, light]: lightView.each()) lightVector.push_back({transform, light});

        return lightVector;
    }

    std::vector<std::pair<const Transform&, const SpotLight&>> LightingSystem::GetSpotLightInfo(entt::registry &registry) {
        auto lightVector = std::vector<std::pair<const Transform&,const SpotLight&>>();

        auto lightView = registry.view<const Transform, const SpotLight>();
        for (auto &&[entity, transform, light]: lightView.each()) lightVector.push_back({transform, light});

        return lightVector;
    }
}
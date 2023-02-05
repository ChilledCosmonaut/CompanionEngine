#pragma once

#include "engine/ECS/System.h"
#include "engine/ECS/Registry.h"

#include "../Components/InfoFlags.h"
#include "../Components/Health.h"

namespace gl3::game {
    class InfoSystem : public engine::entityComponentSystem::System {
    public:
        InfoSystem() = default;

        void OnSetUp(engine::Game &game) override {};

        void Update(engine::Game &game) override {
            auto &registry = engine::Ecs::Registry::getCurrent();

            auto playerInfoView = registry.view<PlayerHealth, engine::Graphics::Text, engine::Graphics::Transform>();
            for (auto &playerInfo: playerInfoView) {
                auto &playerInfoText = playerInfoView.get<engine::Graphics::Text>(playerInfo);
                auto &playerInfoTransform = playerInfoView.get<engine::Graphics::Transform>(playerInfo);

                if (!engine::Ecs::Registry::HasComponent<Health>(playerInfoTransform.parent)) continue;
                auto &health = registry.get<Health>(playerInfoTransform.parent);

                playerInfoText.content = "Player Health: " + std::to_string((int) health.currentLife);
            }

            auto stationInfoView = registry.view<StationHealth, engine::Graphics::Text, engine::Graphics::Transform>();
            for (auto &stationInfo: stationInfoView) {
                auto &stationInfoText = stationInfoView.get<engine::Graphics::Text>(stationInfo);
                auto &stationInfoTransform = stationInfoView.get<engine::Graphics::Transform>(stationInfo);

                auto stationView = registry.view<Station, Health>();
                for (auto &entity: stationView) {
                    auto &stationHealth = stationView.get<Health>(entity);

                    stationInfoText.content = "Station Health: " + std::to_string((int) stationHealth.currentLife);
                }
            }

            auto enemyCountView = registry.view<EnemyCount, engine::Graphics::Text, engine::Graphics::Transform>();
            for (auto &enemyCount: enemyCountView) {
                auto &enemyCountText = enemyCountView.get<engine::Graphics::Text>(enemyCount);
                auto &enemyCountTransform = enemyCountView.get<engine::Graphics::Transform>(enemyCount);

                auto waveInfoView = registry.view<WaveInfo>();
                for (auto &entity: waveInfoView) {
                    auto &waveInfo = waveInfoView.get<WaveInfo>(entity);

                    enemyCountText.content = "Enemies alive: " + std::to_string((int) waveInfo.enemiesAlive);
                }
            }

            auto waveCountView = registry.view<WaveCount, engine::Graphics::Text, engine::Graphics::Transform>();
            for (auto &waveCount: waveCountView) {
                auto &waveCountText = waveCountView.get<engine::Graphics::Text>(waveCount);
                auto &waveCountTransform = waveCountView.get<engine::Graphics::Transform>(waveCount);

                auto waveInfoView = registry.view<WaveInfo>();
                for (auto &entity: waveInfoView) {
                    auto &waveInfo = waveInfoView.get<WaveInfo>(entity);

                    waveCountText.content = "Wave No.: " + std::to_string((int) waveInfo.waveCounter);
                }
            }
        };

        void OnShutdown(engine::Game &engine) override {};
    };
}
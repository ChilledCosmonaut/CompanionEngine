#include "SpawnSystem.h"

namespace gl3::game {

    void SpawnSystem::Update(engine::Game &game) {
        auto &registry = engine::Ecs::Registry::getCurrent();

        auto waveView = registry.view<WaveInfo, NewWave>();

        for (auto &gameController: waveView) {
            auto &waveInfo = waveView.get<WaveInfo>(gameController);
            auto &newWave = waveView.get<NewWave>(gameController);

            engine::Scene *scene = game.getCurrentScene();

            waveInfo.waveCounter += newWave.waveCount;
            engine::Ecs::Registry::DestroyComponentWithoutFlag<NewWave>(gameController);

            auto nextEnemyCount = pow(waveInfo.waveCounter, 2.f) / pow(waveInfo.waveCounter, 5.f / 4.f) + waveInfo.baseEnemyCount;

            float carrierCount = round(nextEnemyCount / 3);
            float fighterCount = round(nextEnemyCount * 2 / 3);

            waveInfo.enemiesAlive = carrierCount + fighterCount;

            std::random_device randDevPos;
            std::mt19937 posGenerator(randDevPos());
            std::uniform_int_distribution<int> posDistribution(230, 280);

            std::random_device randDevRot;
            std::mt19937 rotGenerator(randDevRot());
            std::uniform_int_distribution<int> rotDistribution(0, 360);

            std::random_device randDevLateralOffset;
            std::mt19937 lateralOffsetGenerator(randDevLateralOffset());
            std::normal_distribution<> lateralOffsetDistribution(-10, 10);

            for (int fighterIndex = 0; fighterIndex < fighterCount; ++fighterIndex) {
                entt::entity enemy = Utils::ModelCreationTemplates::CreateEnemyVariant1(scene);
                auto &transform = registry.get<engine::Graphics::Transform>(enemy);
                transform.translation = glm::quat(glm::radians(glm::vec3(0, rotDistribution(rotGenerator), 0))) *
                                        glm::vec3(posDistribution(posGenerator),
                                                  lateralOffsetDistribution(lateralOffsetGenerator), 0);
            }

            for (int carrierIndex = 0; carrierIndex < carrierCount; ++carrierIndex) {
                entt::entity enemy = Utils::ModelCreationTemplates::CreateCarrier(scene);
                auto &transform = registry.get<engine::Graphics::Transform>(enemy);
                transform.translation = glm::quat(glm::radians(glm::vec3(0, rotDistribution(rotGenerator), 0))) *
                                        glm::vec3(posDistribution(posGenerator),
                                                  lateralOffsetDistribution(lateralOffsetGenerator), 0);
            }

            std::cout<<"Spawned: " + std::to_string(carrierCount) + " carriers and " + std::to_string(fighterCount) + " fighters."<<std::endl;
        }
    }
}
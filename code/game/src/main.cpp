#include "engine/Systems/Graphics/shader.h"
#include "ShipController.h"
#include "Enemy Controller.h"
#include "ProjectileSystem.h"
#include "engine/Tools/Grid.h"
#include "engine/Systems/Sound/Components/SpatialAudioSource.h"
#include "engine/Game.h"

#include "SampleScene.h"

using namespace gl3::engine;
using namespace gl3::game;

int main() {

    Game game = Game(1920, 1080, "A Journey through Space");

    Graphics::shader litShader = Graphics::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    ShipController shipController {};

    shipController.SetUpSystem(game);

    EnemyController enemyController {};

    enemyController.SetUpSystem(game);

    ProjectileSystem projectileSystem {};

    projectileSystem.SetUpSystem(game);

    auto scene = SampleScene();

    game.ChangeActiveSceneTo(&scene);

    Graphics::shader shader = Graphics::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Graphics::Components::Transform standardTransform =
            Graphics::Components::Transform(
                    glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,0.5f));

    ShipController controller1 = ShipController();

    game.onStartup.addListener([&] (Game &game){
        auto registry = game.getCurrentScene()->getRegistry();
        auto audioSources = registry->view<soundSystem::AudioSource>();
        for (auto &audioEntity:audioSources) {
            soundSystem::AudioSourceUtils::Play(audioEntity, scene, registry->get<soundSystem::AudioSource>(audioEntity), false);
        }
    });

    game.run();

    return 0;
}
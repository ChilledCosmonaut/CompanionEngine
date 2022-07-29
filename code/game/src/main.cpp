#include "engine/GraphicsEngine/shader.h"
#include "ShipController.h"
#include "Enemy Controller.h"
#include "ProjectileSystem.h"
#include "engine/Tools/Grid.h"
#include "engine/SoundSystem/AudioListener.h"
#include "engine/SoundSystem/AudioSource.h"
#include "engine/Game.h"

#include "SampleScene.h"
#include "../../engine/src/GraphicsEngine/GraphicsSystem.h"

using namespace gl3::engine;
using namespace gl3::game;

const float W_WIDTH = 1920.0f;
const float W_HEIGHT = 1080.0f;
const char *W_TITLE = "GameLab III";

int main() {

    Game game = Game(1280, 720, "A Journey through Space");

    Graphics::shader litShader = Graphics::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Graphics::Systems::GraphicsSystem graphicsSystem {};

    graphicsSystem.SetUpSystem(game);

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

    soundSystem::AudioListener::StartAudioListener(&standardTransform);

    ShipController controller1 = ShipController();

    game.onStartup.addListener([&] (Game &game){
        auto registry = game.getCurrentScene()->getRegistry();
        auto audioSources = registry->view<soundSystem::AudioSource>();
        for (auto &audioEntity:audioSources) {
            soundSystem::AudioSourceUtils::PlayBackground(registry->get<soundSystem::AudioSource>(audioEntity), true);
        }
    });

    game.run();

    soundSystem::AudioListener::StopAudioListener();

    return 0;
}
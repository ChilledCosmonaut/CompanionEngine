#include "Systems/ShipController.h"
#include "Systems/EnemyController.h"
#include "Systems/LaserSystem.h"
#include "Systems/AsteroidVectorField.h"
#include "Systems/SpawnSystem.h"
#include "Systems/InfoSystem.h"

#include "engine/Game.h"

#include "SampleScene.h"

using namespace gl3::engine;
using namespace gl3::game;

int main() {

    Game game = Game(1920, 1080, "A Journey through Space");

    ShipController shipController {};

    shipController.SetUpSystem(game);

    InfoSystem infoSystem {};

    infoSystem.SetUpSystem(game);

//    GameOverSystem gameOverSystem {};
//
//    gameOverSystem.SetUpSystem(game);

    SpawnSystem spawnSystem {};

    spawnSystem.SetUpSystem(game);

    AsteroidVectorField asteroidVectorField {};

    asteroidVectorField.SetUpSystem(game);

    EnemyController enemyController {};

    enemyController.SetUpSystem(game);

    LaserSystem projectileSystem {};

    projectileSystem.SetUpSystem(game);

    auto scene = SampleScene();

    game.ChangeActiveSceneTo(&scene);

    Graphics::Transform standardTransform =
            Graphics::Transform(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,0.5f));

    ShipController controller1 = ShipController();

    game.run();

    return 0;
}
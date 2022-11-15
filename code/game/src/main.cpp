#include "ShipController.h"
#include "Enemy Controller.h"
#include "ProjectileSystem.h"
#include "engine/Tools/Grid.h"
#include "engine/Game.h"

#include "SampleScene.h"

using namespace gl3::engine;
using namespace gl3::game;

int main() {

    Game game = Game(1920, 1080, "A Journey through Space");

    ShipController shipController {};

    shipController.SetUpSystem(game);

    EnemyController enemyController {};

    enemyController.SetUpSystem(game);

    ProjectileSystem projectileSystem {};

    projectileSystem.SetUpSystem(game);

    auto scene = SampleScene();

    game.ChangeActiveSceneTo(&scene);

    Graphics::Transform standardTransform =
            Graphics::Transform(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,0.5f));

    ShipController controller1 = ShipController();

    game.run();

    return 0;
}
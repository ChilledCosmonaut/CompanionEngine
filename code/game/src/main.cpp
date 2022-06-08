#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/GraphicsEngine/shader.h"
#include <iostream>
#include "ShipController.h"
#include "engine/GraphicsEngine/camera.h"
#include "engine/InputSystem/InputManager.h"
#include "engine/GraphicsEngine/Model.h"
#include "engine/Tools/Grid.h"
#include "engine/SoundSystem/AudioListener.h"
#include "engine/SoundSystem/AudioSource.h"
#include "engine/Time.h"
#include "engine/Game.h"

#include "SampleScene.h"
#include "engine/GraphicsEngine/Systems/GraphicsSystem.h"

using namespace gl3::engine;
using namespace gl3::game;

const float W_WIDTH = 1920.0f;
const float W_HEIGHT = 1080.0f;
const char *W_TITLE = "GameLab III";

// camera
Graphics::Camera *camera;
float lastX = W_WIDTH / 2.0f;
float lastY = W_HEIGHT / 2.0f;
bool firstMouse = true;

float zRotation = 0.0f;
float rotStep = 90.0f;
float xTranslate = 0.0f, yTranslate = 0.0f;
float transStep = 20.0f;

float mouseOffset = 20.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);
glm::vec3 shipPos1 = glm::vec3(5.0f, -95.0f, -55.0f);
glm::vec3 shipPos2 = glm::vec3(20.0f, -65.0f, -50.0f);
glm::vec3 shipPos3 = glm::vec3(40.0f, -90.0f, -60.0f);

glm::vec3 rota = glm::vec3(0,0,0);

int currentVisiblePlane = 3;

auto modelMatrixTransform = Graphics::Components::Transform(rota, glm::vec3(0, 0, -10.0f));

float yaw = -90.0f, pitch = 0.0f, fov = 45.0f;


void modelTransform(Graphics::shader *shaderProgram);//unsigned int shaderProgram);
void viewTransform(Graphics::shader *shaderProgram);//unsigned int shaderProgram);
void projectionTransform(Graphics::shader *shaderProgram);//unsigned int shaderProgram);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float mousePosX = xposIn - (float) W_WIDTH / 2;
    float mousePosY = yposIn - (float) W_HEIGHT / 2;

    mousePosX /= W_WIDTH / 2.0f;
    mousePosY /= W_HEIGHT / 2.0f;

    if (mousePosX < mouseOffset && mousePosX > -mouseOffset) mousePosX = 0;
    if (mousePosY < mouseOffset && mousePosY > -mouseOffset) mousePosY = 0;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processUserInput(GLFWwindow *window, int key, int scancode, int action, int mods) {

    const float cameraSpeed = 0.5f * Time::GetDeltaTime(); // adjust accordingly

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_UP){
        rota.x += 10 * Time::GetDeltaTime();
        modelMatrixTransform.SetRotation(rota);
        std::cout << rota.x << std::endl;
    }


    // user input
    if (key == GLFW_KEY_D) {
        camera->ProcessKeyboard(Graphics::RIGHT, Time::GetDeltaTime());
        //std::cout<<"Pressed D" + to_string(deltaTime) <<endl;
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        //zRotation -= rotStep * deltaTime;
    }

    if (key == GLFW_KEY_A) {
        camera->ProcessKeyboard(Graphics::LEFT, Time::GetDeltaTime());
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        //zRotation += rotStep * deltaTime;
    }

    if (key == GLFW_KEY_W) {
        camera->ProcessKeyboard(Graphics::FORWARD, Time::GetDeltaTime());
        //*yTranslate += sin(glm::radians(zRotation)) * transStep * deltaTime;
        xTranslate += cos(glm::radians(zRotation)) * transStep * Time::GetDeltaTime();//*
        //cameraPos += cameraSpeed * cameraFront;
    }

    if (key == GLFW_KEY_S) {
        camera->ProcessKeyboard(Graphics::BACKWARD, Time::GetDeltaTime());
        //cameraPos -= cameraSpeed * cameraFront;
        //*yTranslate -= sin(glm::radians(zRotation)) * transStep * deltaTime;
        xTranslate -= cos(glm::radians(zRotation)) * transStep * Time::GetDeltaTime();//*
    }

    if (key == GLFW_KEY_SPACE) {
        /*shipPos1.z += transStep * deltaTime;
        shipPos2.z += transStep * deltaTime;
        shipPos3.z += transStep * deltaTime;*/
    }
}

void updateKeys(GLFWwindow *window) {

    const float cameraSpeed = 0.5f * Time::GetDeltaTime(); // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main() {

    Game game = Game(1280, 720, "A Journey through Space");

    Graphics::shader litShader = Graphics::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Graphics::Model model4 = Graphics::Model("../../assets/backpack.obj");
    Graphics::Model model1 = Graphics::Model("../../assets/SpaceShip4.obj");
    Graphics::Model model2 = Graphics::Model("../../assets/SpaceShip2.obj");
    Graphics::Model model3 = Graphics::Model("../../assets/SpaceShip3.obj");
    Graphics::Model asteroid = Graphics::Model("../../assets/asteriod1.obj");
    Graphics::Model playerShip("../../assets/playerShip.obj");
    Graphics::Model radarCubeModel = Graphics::Model("../../assets/RadarBox.obj");

    Graphics::Systems::GraphicsSystem graphicsSystem {};

    graphicsSystem.SetUpSystem(game);

    auto scene = SampleScene();

    game.ChangeActiveSceneTo(&scene);

    /*Graphics::Scene radarScene = Graphics::Scene();

    camera = scene.getCamera();*/

    Graphics::shader shader = Graphics::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Graphics::Components::Transform model1Transform = Graphics::Components::Transform(glm::vec3(-90.0f,180.0f,0.0f), shipPos1);

    std::cout<<"Generating Grid"<<std::endl;

    auto startTime = glfwGetTime();

    tools::Grid grid = tools::Grid(glm::vec3(0,0,0));

    Graphics::Components::Transform standardTransform = Graphics::Components::Transform(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Components::Transform standardTransform2 = Graphics::Components::Transform(glm::vec3(0,0,0),glm::vec3(-5,3,14),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Components::Transform standardTransform3 = Graphics::Components::Transform(glm::vec3(0,0,0),glm::vec3(0,12,5),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Components::Transform standardTransform4 = Graphics::Components::Transform(glm::vec3(0,0,0),glm::vec3(20,-10,0),glm::vec3(0.5f,0.5f,0.5f));

    //scene.AddSceneModels(asteroid, &shader, &standardTransform);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform2);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform3);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform4);

    //scene.AddSceneModels(playerShip, &shader, camera->GetTransform());

    soundSystem::AudioListener::StartAudioListener(&standardTransform);

    soundSystem::AudioSource audioSource = soundSystem::AudioSource("../../assets/audio/electronic-wave.mp3", &standardTransform4);

    ShipController controller1 = ShipController();
    auto endTime = glfwGetTime();

    auto calculationTime = endTime - startTime;

    std::cout<<calculationTime<<std::endl;

    auto startTime2 = glfwGetTime();

    //grid.VisualizeGrid(&radarScene, &radarCubeModel, &shader);

    auto endTime2 = glfwGetTime();

    auto calculationTime2 = endTime2 - startTime2;

    std::cout<<calculationTime2<<std::endl;

    grid.SwitchVisiblePlane(currentVisiblePlane);

    audioSource.PlayBackground(true);

    /*updateKeys(game.getWindow());

    game.onBeforeUpdate.addListener([&](Game& game) {
        updateKeys(game.getWindow());

        controller1.GetUpdatedShipPosition(camera->GetTransform(), game.getWindow(), &W_WIDTH, &W_HEIGHT, Time::GetDeltaTime());
    });*/

    game.run();

    soundSystem::AudioListener::StopAudioListener();

    return 0;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
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

using namespace gl3::engine;

const float W_WIDTH = 1920.0f;
const float W_HEIGHT = 1080.0f;
const char *W_TITLE = "GameLab III";

// camera
Camera *camera;
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

auto modelMatrixTransform = Graphics::Transform(rota, glm::vec3(0, 0, -10.0f));

float yaw = -90.0f, pitch = 0.0f, fov = 45.0f;


void modelTransform(gl3::shader *shaderProgram);//unsigned int shaderProgram);
void viewTransform(gl3::shader *shaderProgram);//unsigned int shaderProgram);
void projectionTransform(gl3::shader *shaderProgram);//unsigned int shaderProgram);

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
        camera->ProcessKeyboard(RIGHT, Time::GetDeltaTime());
        //std::cout<<"Pressed D" + to_string(deltaTime) <<endl;
        //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        //zRotation -= rotStep * deltaTime;
    }

    if (key == GLFW_KEY_A) {
        camera->ProcessKeyboard(LEFT, Time::GetDeltaTime());
        //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        //zRotation += rotStep * deltaTime;
    }

    if (key == GLFW_KEY_W) {
        camera->ProcessKeyboard(FORWARD, Time::GetDeltaTime());
        //*yTranslate += sin(glm::radians(zRotation)) * transStep * deltaTime;
        xTranslate += cos(glm::radians(zRotation)) * transStep * Time::GetDeltaTime();//*
        //cameraPos += cameraSpeed * cameraFront;
    }

    if (key == GLFW_KEY_S) {
        camera->ProcessKeyboard(BACKWARD, Time::GetDeltaTime());
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

    gl3::shader litShader = gl3::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Model model4 = Model("../../assets/backpack.obj");
    Model model1 = Model("../../assets/SpaceShip4.obj");
    Model model2 = Model("../../assets/SpaceShip2.obj");
    Model model3 = Model("../../assets/SpaceShip3.obj");
    Model asteroid = Model("../../assets/asteriod1.obj");
    Model playerShip("../../assets/playerShip.obj");
    Model radarCubeModel = Model("../../assets/RadarBox.obj");

    Graphics::Scene scene = Graphics::Scene();

    game.ChangeActiveSceneTo(&scene);

    Graphics::Scene radarScene = Graphics::Scene();

    camera = scene.getCamera();

    gl3::shader shader = gl3::shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Graphics::Transform model1Transform = Graphics::Transform(glm::vec3(-90.0f,180.0f,0.0f), shipPos1);

    std::cout<<"Generating Grid"<<std::endl;

    auto startTime = glfwGetTime();

    logic::Grid grid = logic::Grid(glm::vec3(0,0,0));

    Graphics::Transform standardTransform = Graphics::Transform(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Transform standardTransform2 = Graphics::Transform(glm::vec3(0,0,0),glm::vec3(-5,3,14),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Transform standardTransform3 = Graphics::Transform(glm::vec3(0,0,0),glm::vec3(0,12,5),glm::vec3(0.5f,0.5f,0.5f));

    Graphics::Transform standardTransform4 = Graphics::Transform(glm::vec3(0,0,0),glm::vec3(20,-10,0),glm::vec3(0.5f,0.5f,0.5f));

    //scene.AddSceneModels(asteroid, &shader, &standardTransform);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform2);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform3);

    //scene.AddSceneModels(asteroid, &shader, &standardTransform4);

    //scene.AddSceneModels(playerShip, &shader, camera->GetTransform());

    Sound::AudioListener::StartAudioListener(&standardTransform);

    Sound::AudioSource audioSource = Sound::AudioSource("../../assets/audio/electronic-wave.mp3", &standardTransform4);

    ShipController controller1 = ShipController();
    auto endTime = glfwGetTime();

    auto calculationTime = endTime - startTime;

    std::cout<<calculationTime<<std::endl;

    auto startTime2 = glfwGetTime();

    grid.VisualizeGrid(&radarScene, &radarCubeModel, &shader);

    auto endTime2 = glfwGetTime();

    auto calculationTime2 = endTime2 - startTime2;

    std::cout<<calculationTime2<<std::endl;

    grid.SwitchVisiblePlane(currentVisiblePlane);

    audioSource.PlayBackground(true);

    controller1.GetUpdatedShipPosition(camera->GetTransform(), game.getWindow(), &W_WIDTH, &W_HEIGHT, Time::GetDeltaTime());

    updateKeys(game.getWindow());

    game.run();

    Sound::AudioListener::StopAudioListener();

    return 0;
}
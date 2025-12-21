#include "Game.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
//------ Classes ---------------------------//
#include "World.h"
#include "..\Settings\WorldSettings.h"
#include "PostProcessing.h"
#include "RessourceManager.h"

Camera Game::mainCamera = Camera(glm::vec3(0.0f, 
    (WorldSettings::HEIGHTOFFSET + WorldSettings::WORLDNOISEAMPLITUDE) / WorldSettings::AMPLIFIERSTRENGTH, 0.0f));

glm::vec3 Game::lightColor = glm::vec3(0.9f, 0.9f, 1.0f);
glm::vec3 Game::lightDirection = glm::vec3(-0.5f, 3.0f, -2.0f);
float Game::ambientStrength = 0.3f;
unsigned int Game::textureAtlas = 0;
unsigned int Game::skybox = 0;

Shader* Game::basicShader;
Shader* Game::diffusedShader;
Shader* Game::skyboxShader;

void Game::Start() {
    Game::textureAtlas = RessourceManager::CreateTexture("Resources/Textures/TextureAtlasColored.png");
    Game::skybox = RessourceManager::CreateCubeMap(Environment::SKYBOXCUBEMAP1);

    Game::basicShader = new Shader("Resources/Shader/diffusedVertex.glsl", "Resources/Shader/diffusedFragment.glsl");
    Game::diffusedShader = new Shader("Resources/Shader/diffusedVertex.glsl", "Resources/Shader/diffusedFragment.glsl");
    Game::skyboxShader = new Shader("Resources/Shader/skyboxVertex.glsl", "Resources/Shader/skyboxFragment.glsl");

    World::Start();
    PostProcessing::Start();

    Game::diffusedShader->use();
    Game::diffusedShader->setInt("texture", 0);

    Game::skyboxShader->use();
    Game::skyboxShader->setInt("skybox", 0);
}

void Game::Update(float deltaTime) {
    
}

void Game::Render(int screenWidth, int screenHeight) {
    glCullFace(GL_FRONT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Game::diffusedShader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Game::textureAtlas);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(GameSettings::FIELDOFVIEW), (float)screenWidth / (float)screenHeight, GameSettings::NEARPLANE, GameSettings::FARPLANE);
    Game::diffusedShader->setMat4("projection", projection);

    glm::mat4 view;
    view = Game::mainCamera.GetViewMatrix();
    Game::diffusedShader->setMat4("view", view);

    World::Render(*Game::diffusedShader);

    Game::skyboxShader->use();
    glCullFace(GL_BACK);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Game::skybox);

    view = glm::mat4(glm::mat3(Game::mainCamera.GetViewMatrix()));
    Game::skyboxShader->setMat4("view", view);
    Game::skyboxShader->setMat4("projection", projection);

    PostProcessing::Render(*Game::skyboxShader);
}

void Game::LateUpdate(float deltaTime) {

}

void Game::ProcessInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float baseSpeed = 5.0f * deltaTime;
    const float speedAmplifier = 1.5f;
    float cameraSpeed = baseSpeed;
    float moveX = 0.0f;
    float moveY = 0.0f;
    float moveZ = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveZ += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveZ -= 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveX -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveX += 1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        moveY -= 1;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        moveY += 1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed *= speedAmplifier;

    glm::vec2 moveHori(moveX, moveZ);
    if (glm::length(moveHori) > 0.0f)
        moveHori = glm::normalize(moveHori);

    glm::vec3 moveVector(moveHori.x, moveY, moveHori.y);
    Game::mainCamera.Move(moveVector * cameraSpeed);
}

void Game::MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (Game::mainCamera.firstMouse)
    {
        Game::mainCamera.lastX = xpos;
        Game::mainCamera.lastY = ypos;
        Game::mainCamera.firstMouse = false;
    }

    float xoffset = xpos - Game::mainCamera.lastX;
    float yoffset = Game::mainCamera.lastY - ypos;
    Game::mainCamera.lastX = xpos;
    Game::mainCamera.lastY = ypos;

    Game::mainCamera.ProcessMouseMovement(xoffset, yoffset);
}

void Game::Stop() {
    delete Game::basicShader;
    delete Game::diffusedShader;
    delete Game::skyboxShader;
}
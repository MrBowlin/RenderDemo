#include "Game.h"
//------ C++ Standard Libraries ------------//
//------ GLFW, GLM and GLAD ----------------//
#include <glm/gtc/matrix_transform.hpp>
//------ Classes ---------------------------//

Camera Game::mainCamera;
World Game::world;

glm::vec3 Game::lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 Game::lightDirection = glm::vec3(-0.5f, 3.0f, -2.0f);
float Game::ambientStrength = 0.3f;

void Game::Start() {
    Game::world.Start();
}

void Game::Update(float deltaTime) {
    
}

void Game::Render(Shader shader, int screenWidth, int screenHeight) {
    shader.use();
    shader.setVec3("lightColor", Game::lightColor);
    shader.setVec3("lightDirection", Game::lightDirection);
    shader.setFloat("ambientStrength", Game::ambientStrength);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(80.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view;
    view = Game::mainCamera.GetViewMatrix();
    shader.setMat4("view", view);

    Game::world.Render(shader);
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
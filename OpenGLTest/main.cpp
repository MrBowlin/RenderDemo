#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.h"
#include "stb_image.h"
#include "Classes/Camera.h"
#include "Classes/Chunk.h"
#include "Classes/RessourceManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

Camera camera;
RessourceManager ressourceManager;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightDirection(-0.5f, 3.0f, -2.0f);
float ambientStrength = 0.3f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader basicShader("Ressources/Shader/diffusedVertex.glsl", "Ressources/Shader/diffusedFragment.glsl");
    Shader diffusedShader("Ressources/Shader/diffusedVertex.glsl", "Ressources/Shader/diffusedFragment.glsl");
    Shader activeShader = diffusedShader;

    Chunk chunk = Chunk();
    chunk.Start();

    // Produces Stack Warning!
    unsigned int texture;
    ressourceManager.CreateTexture(activeShader, &texture);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);
        glfwSetCursorPosCallback(window, mouse_callback);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        activeShader.use();
        activeShader.setVec3("lightColor", lightColor);
        activeShader.setVec3("lightDirection", lightDirection);
        activeShader.setFloat("ambientStrength", ambientStrength);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(80.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        activeShader.setMat4("projection", projection);

        glm::mat4 view;
        view = camera.GetViewMatrix();
        activeShader.setMat4("view", view);

        chunk.Render(activeShader);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
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
    camera.Move(moveVector * cameraSpeed);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
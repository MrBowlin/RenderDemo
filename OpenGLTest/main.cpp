#include <iostream>

#include "Classes/Game.h"
#include "Resources/Properties/Environment.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

int width = 0;
int height = 0;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

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
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Game::Start();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Game::ProcessInput(window, deltaTime);
        glfwSetCursorPosCallback(window, Game::MouseCallback);

        Game::Update(deltaTime);

        Game::Render(SCR_WIDTH, SCR_HEIGHT); // sollte width, height sein, aber sind gerade beide noch 0
      
        Game::LateUpdate(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Game::Stop();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int inwidth, int inheight)
{
    glViewport(0, 0, inwidth, inheight);
    width = inwidth;
    height = inheight;
}
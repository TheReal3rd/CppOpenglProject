#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Transform.h"
#include "Graphics/Renderer.h"

const char* vertexShader = R"(
#version 330 core
layout (location = 0) in vec2 pos;
uniform vec2 uOffset;
uniform vec2 uScale;
void main()
{
    vec2 scaled = pos * uScale;
    gl_Position = vec4(scaled + uOffset, 0.0, 1.0);
}
)";

const char* fragmentShader = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 uColour;
void main()
{
    FragColor = uColour;
}
)";

bool wireFrameMode = false;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void processGameplayInput(GLFWwindow *window) 
{

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    else if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        wireFrameMode = !wireFrameMode;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pong (OpenGL, GLFW and C++)", nullptr, nullptr);
    if (window == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initilize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    Mesh squareMesh(vertices, sizeof(vertices), indices, sizeof(indices));
    Shader shader(vertexShader, fragmentShader);
    Renderer renderer;

    /*
        position(x, y), scale(sx, sy), colour(r, g, b, a)
    */
    std::vector<Drawable> objects = {
        { &squareMesh, &shader, { 0.0f,  0.0f, 0.8f, 0.8f }, 1, 0, 0, 1 },
        { &squareMesh, &shader, {  0.0f,  0.0f, 0.2f, 0.6f }, 0, 1, 0, 0.5 },
        { &squareMesh, &shader, {  0.6f,  0.0f, 0.5f, 0.2f }, 0, 0, 1, 0.5 }
    };

    while (!glfwWindowShouldClose(window))
    {
        processGameplayInput(window);
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (wireFrameMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (const auto& obj : objects)
            renderer.draw(obj);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



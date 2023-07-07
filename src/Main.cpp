#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>

#include "Renderer.h"


const char* vertexShaderPath = "res/shaders/Shader.vs";
const char* fragmentShaderPath = "res/shaders/Shader.fs";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Enable OpenGL debug mode */
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Glew not ok" << std::endl;

    /* Set error callback function */
    glDebugMessageCallback(ErrorCB, nullptr);

    unsigned int quad_count = 4 * 2;

    float quad_points[quad_count] = {
        -1.0f, -1.0f, // 0
         1.0f, -1.0f, // 1
        -1.0f,  1.0f, // 2
         1.0f,  1.0f  // 3
    };

    unsigned int indices_count = 2 * 3;
    unsigned int indices[indices_count] = {
        0, 1, 3,
        0, 3, 2
    };

    Renderer renderer;

    VertexArray va;
    VertexBuffer vb(quad_points, quad_count * sizeof(float), GL_STATIC_DRAW);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    
    va.AddBuffer(vb, layout);
    
    IndexBuffer ib(indices, indices_count, GL_STATIC_DRAW);
    
    Shaders shaders;

    shaders.AddShader(GL_VERTEX_SHADER, vertexShaderPath);
    shaders.AddShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    shaders.Create();
    
    shaders.Bind();

    shaders.SetUniform4f("screenSize", 960, 540, 1920, 1080);

    float accuracy = 1;
    float delta = 1.01;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        shaders.Bind();
        shaders.SetUniform1f("accuracy", accuracy);

        renderer.DrawTriangle(va, shaders, ib);

        accuracy *= delta;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
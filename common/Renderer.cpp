#include <iostream>

#include "Renderer.h"

void ErrorCB (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << std::endl;
    if (type != GL_DEBUG_TYPE_ERROR_ARB)
    {
        std::cout << "OpenGL Debug:\n" << message << std::endl;
        return;
    }
    std::cout << "====================\n";
    std::cout << "=== OPENGL ERROR ===\n";
    std::cout << "====================\n";
    std::cout << "Source : ";
    switch (source)
    {
        case GL_DEBUG_SOURCE_API_ARB:
            std::cout << "API\n";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
            std::cout << "Window\n";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
            std::cout << "Shader Compiler\n";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
            std::cout << "Third Party\n";
            break;
        case GL_DEBUG_SOURCE_APPLICATION_ARB:
            std::cout << "Source Application\n";
            break;
        default:
            std::cout << "Unknown\n";
            break;
    }
    std::cout << "OpenGL Error: " << message << std::endl;
    std::cout << "Severity: " << (severity > 0x9146 ? (severity > 0x9147 ? "Low" : "Medium") : "High")  << std::endl;
}

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::DrawTriangle(const VertexArray& va, const Shaders& shaders, const IndexBuffer& ib)
{
    va.Bind();
    shaders.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
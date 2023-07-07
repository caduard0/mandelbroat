#pragma once

#include "GL/glew.h"

#include "VertexArray.h"
#include "Shaders.h"
#include "IndexBuffer.h"


void ErrorCB (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

class Renderer
{
private:

public:
    Renderer();
    ~Renderer();

    void DrawTriangle(const VertexArray& va, const Shaders& shaders, const IndexBuffer& ib);
    void Clear();
};
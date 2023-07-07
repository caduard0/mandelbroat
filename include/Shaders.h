#pragma once

#include <vector>
#include <unordered_map>

#include "GL/glew.h"

class Shaders
{
private:
    unsigned int m_RendererID;
    std::vector<unsigned int> m_Shaders;
    std::unordered_map<const char*, int> m_UniformLocationCache;
public:
    Shaders();
    ~Shaders();

    void AddShader(unsigned int type, const char* path);
    
    void Create();

    void Bind() const;
    void Unbind() const;

    // Change when math.h made
    void SetUniform1f(const char* name, float x);

    void SetUniform4f(const char* name, float x, float y, float z, float w);

    /* TODO
    template<typename T>
    void AddUniform(const char* name);
    */
private:
    int GetUniformLocation(const char* name);
};
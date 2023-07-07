#include "Utils.h"
#include <iostream>

#include "Shaders.h"

Shaders::Shaders()
    :m_RendererID(0) {}

Shaders::~Shaders()
{
    glDeleteProgram(m_RendererID);
}

void Shaders::AddShader(unsigned int type, const char* path)
{
    std::string source = ReadFile(path);

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE || source.length() <= 0)
    {
        std::cout << "Failed to compile " <<
                    (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
                    << " shader" << std::endl;
        glDeleteShader(id);

        m_Shaders.push_back(0);
        return;
    }

    m_Shaders.push_back(id);
}

void Shaders::Create()
{
    m_RendererID = glCreateProgram();

    for (int i = 0; i < m_Shaders.size(); i++)
    {
        unsigned int shader = m_Shaders[i];

        glAttachShader(m_RendererID, shader);

        glDeleteShader(shader);
    }

    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
}

void Shaders::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shaders::Unbind() const
{
    glUseProgram(0);
}

void Shaders::SetUniform1f(const char* name, float x)
{
    int location = GetUniformLocation(name);
    glUniform1f(location, x);
}

void Shaders::SetUniform4f(const char* name, float x, float y, float z, float w)
{
    int location = GetUniformLocation(name);
    glUniform4f(location, x, y, z, w);
}

/* TODO
template<>
void Shaders::AddUniform<float>(const char* name)
{

}
*/

int Shaders::GetUniformLocation(const char* name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name);
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesnt exist!\n";
    
    m_UniformLocationCache[name] = location;
    return location;
}
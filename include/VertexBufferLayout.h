#pragma once

#include <vector>

#include "GL/glew.h"

struct VertexBufferElements
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    VertexBufferElements(unsigned int _type, unsigned int _count, unsigned char _normalized)
        : type(_type), count(_count), normalized(_normalized) {}

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:          return 4;
        case GL_UNSIGNED_INT:   return 4;
        case GL_UNSIGNED_BYTE:  return 1;
        }

        return 0;
    } 
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElements> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count);

    inline const std::vector<VertexBufferElements>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }

};
#pragma once
#include <memory>
#include <type_traits>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>


namespace llgl
{
class VertexBuffer;
class ElementBuffer;

class VertexArray
{
public:
    using uint = unsigned int;

    VertexArray();
    ~VertexArray();

    void bind();
    static void unbind();

    template<typename AttribType = float>
    bool setAttrib(uint index, uint attribNumber, int fullSize, int offset,
    std::shared_ptr<VertexBuffer> buffer, bool normalized = false);

    bool setAttrib(uint index, uint attribNumber, int typeEnum, int fullSize,
    int offset, std::shared_ptr<VertexBuffer> buffer, bool normalized = false);

private:
    unsigned int vao{};
    std::vector<std::shared_ptr<VertexBuffer>> vbos;
};


template<typename AttribType>
bool VertexArray::setAttrib(uint index, uint attribNumber, int fullSize,
int offset, std::shared_ptr<VertexBuffer> buffer, bool normalized)
{
    int typeEnum{};
    if constexpr(std::is_same_v<AttribType, float>) {
        typeEnum = GL_FLOAT;
    }
    else if constexpr(std::is_same_v<AttribType, int>) {
        typeEnum = GL_INT;
    }
    else if constexpr(std::is_same_v<AttribType, unsigned int>) {
        typeEnum = GL_UNSIGNED_INT;
    }
    else if constexpr(std::is_same_v<AttribType, char>) {
        typeEnum = GL_BYTE;
    }
    else if constexpr(std::is_same_v<AttribType, unsigned char>) {
        typeEnum = GL_UNSIGNED_BYTE;
    }
    else if constexpr(std::is_same_v<AttribType, short>) {
        typeEnum = GL_SHORT;
    }
    else if constexpr(std::is_same_v<AttribType, unsigned short>) {
        typeEnum = GL_UNSIGNED_SHORT;
    }
    return setAttrib(
    index, attribNumber, typeEnum, fullSize, offset, buffer, normalized);
}


} // namespace llgl

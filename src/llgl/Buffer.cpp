#include "Buffer.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

Buffer::Buffer()
{
    glGenBuffers(1, &this->id);
}

Buffer::~Buffer()
{
    if(this->id) {
        glDeleteBuffers(1, &this->id);
    }
}

void Buffer::allocate(const void *data, int size)
{
    glBindBuffer(this->getBufforTypeId(), this->id);
    glBufferData(this->getBufforTypeId(), size, data, GL_STATIC_DRAW);
}

void Buffer::changeDate(const void *data, int size)
{
    glNamedBufferSubData(this->id, 0, size, data);
}

void Buffer::bind()
{
    glBindBuffer(this->getBufforTypeId(), id);
}

void Buffer::unbind()
{
    glBindBuffer(this->getBufforTypeId(), 0);
}

} // namespace llgl

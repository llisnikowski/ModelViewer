#include "ElementBuffer.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

unsigned int ElementBuffer::getBufforTypeId()
{
    return GL_ELEMENT_ARRAY_BUFFER;
}

void ElementBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


} // namespace llgl

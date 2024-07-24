#include "ElementBuffer.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

unsigned int ElementBuffer::getBufforTypeId()
{
    return GL_ELEMENT_ARRAY_BUFFER;
}


} // namespace llgl

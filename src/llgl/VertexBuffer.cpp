#include "VertexBuffer.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

unsigned int VertexBuffer::getBufforTypeId()
{
    return GL_ARRAY_BUFFER;
}


} // namespace llgl

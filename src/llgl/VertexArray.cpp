#include "VertexArray.hpp"
#include <algorithm>
#include "llgl/VertexBuffer.hpp"


namespace llgl
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->vao);
}

VertexArray::~VertexArray()
{
    if(this->vao) {
        glDeleteVertexArrays(1, &this->vao);
    }
}

void VertexArray::bind()
{
    glBindVertexArray(this->vao);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

bool VertexArray::setAttrib(uint index, uint attribNumber, int typeEnum,
int fullSize, int offset, std::shared_ptr<VertexBuffer> buffer, bool normalized)
{
    if(typeEnum == 0) return false;
    if(!buffer) return false;

    if(std::find(this->vbos.begin(), this->vbos.end(), buffer)
       == this->vbos.end())
    {
        this->vbos.push_back(buffer);
    }

    this->bind();
    buffer->bind();

    glVertexAttribPointer(index, attribNumber, typeEnum, normalized, fullSize,
    reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(index);
    return true;
}


} // namespace llgl

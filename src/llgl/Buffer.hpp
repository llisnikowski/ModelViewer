#pragma once
#include "llgl/Buffer.hpp"

namespace llgl
{

class Buffer
{
public:
    Buffer();
    virtual ~Buffer();

    void allocate(const void *data, int size);

    void bind();
    void unbind();

protected:
    virtual unsigned int getBufforTypeId() = 0;

private:
    unsigned int id{};
};

} // namespace llgl

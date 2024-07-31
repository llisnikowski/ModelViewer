#pragma once
#include "llgl/Buffer.hpp"

namespace llgl
{

class ElementBuffer : public Buffer
{
public:
    static void unbind();

private:
    unsigned int getBufforTypeId() override;
};

} // namespace llgl

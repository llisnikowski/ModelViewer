#pragma once
#include "llgl/Buffer.hpp"

namespace llgl
{

class ElementBuffer : public Buffer
{
private:
    unsigned int getBufforTypeId() override;
};

} // namespace llgl

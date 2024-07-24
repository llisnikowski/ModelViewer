#pragma once
#include "llgl/Buffer.hpp"

namespace llgl
{

class VertexBuffer : public Buffer
{
private:
    unsigned int getBufforTypeId() override;
};

} // namespace llgl

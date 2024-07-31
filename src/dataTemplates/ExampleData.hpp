#pragma once
#include <array>

struct VertexData
{
    std::array<float, 3> pos;
};


extern VertexData cubeVertices[24];
extern unsigned short cubeIndices[36];
extern unsigned short edgeIndices[56];

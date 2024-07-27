#include "ShadersTemplate.hpp"


const char* simpleVS =
R"--|shader|--(#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main()
{
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)--|shader|--";

const char* simpleFS =
R"--|shader|--(#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(0.5f, 0.8f, 0.4f, 1.0f);
}
)--|shader|--";

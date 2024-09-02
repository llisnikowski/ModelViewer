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

uniform vec3 color;
out vec4 FragColor;

void main()
{
   FragColor = vec4(color, 1.0f);
}
)--|shader|--";

const char* posAndColorVs =
R"--|shader|--(#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 mvp;

out vec3 ourColor;

void main()
{
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   ourColor = aColor;
}
)--|shader|--";

const char* colorFs =
R"--|shader|--(#version 330 core
in vec3 ourColor;

out vec4 FragColor;

void main()
{
   FragColor = vec4(ourColor, 1.0f);
}
)--|shader|--";


const char* pickingVs =
R"--|shader|--(#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
}
)--|shader|--";

const char* pickingFs =
R"--|shader|--(#version 330

uniform uint gObjectIndex;
uniform uint gDrawIndex;

out uvec3 FragColor;

void main()
{
   FragColor = uvec3(gObjectIndex, gDrawIndex, gl_PrimitiveID);
}
)--|shader|--";

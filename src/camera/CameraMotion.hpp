#pragma once
#include "glm/glm.hpp"


struct CameraMotion
{
    glm::vec3 rotateVector;
    float angle;
    float progress{};
};

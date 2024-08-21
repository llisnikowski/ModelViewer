#pragma once
#include <optional>
#include "glm/glm.hpp"


struct CameraMotion
{
    glm::vec3 rotateVector;
    float angle;
    std::optional<glm::vec3> postAlign;

    float progress{};
};

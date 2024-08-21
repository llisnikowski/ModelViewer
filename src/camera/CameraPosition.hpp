#pragma once
#include <optional>
#include "glm/glm.hpp"

struct CameraPosition
{
    std::optional<glm::vec3> rotation{};
    bool alignRotation{};

    void setRotation(glm::vec3 position);
};

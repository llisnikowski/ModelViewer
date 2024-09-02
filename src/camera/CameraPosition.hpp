#pragma once
#include <optional>
#include "glm/glm.hpp"

struct CameraPosition
{
    std::optional<glm::vec3> rotation{};
    bool alignRotation{};

    std::optional<float> axisRotation{};

    void setRotation(glm::vec3 position);
    void setAxisRotation(float rot);
};

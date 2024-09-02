#include "CameraPosition.hpp"

void CameraPosition::setRotation(glm::vec3 position)
{
    this->rotation = std::make_optional(position);
}

void CameraPosition::setAxisRotation(float rot)
{
    axisRotation = std::make_optional(rot);
}

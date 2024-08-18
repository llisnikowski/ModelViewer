#include "CameraPosition.hpp"

void CameraPosition::setRotation(glm::vec3 position)
{
    this->rotation = std::make_optional(position);
}

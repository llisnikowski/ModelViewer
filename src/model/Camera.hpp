#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>

class Camera
{
public:
    Camera();

    void setProjectonAspectRatio(double aspect);
    const glm::mat4 &getProjection() const;

    void rotate(glm::vec3 axis, double angle);
    void move(glm::vec3 vector);
    const glm::mat4 &getView() const;

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;

private:
    void updateView();

    glm::mat4 projection{};
    glm::quat rotation{};
    glm::vec3 position{0.f, 0.f, 4};
    glm::mat4 view{};
};

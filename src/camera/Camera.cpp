#include "Camera.hpp"

Camera::Camera()
{
    this->updateView();
}

void Camera::setProjectonAspectRatio(double aspect)
{
    const double zNear = 1.0, zFar = 14.0, fov = 45.0;
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

const glm::mat4 &Camera::getProjection() const
{
    return this->projection;
}

void Camera::rotate(glm::vec3 axis, double angle)
{
    if(axis == glm::vec3(0, 0, 0)) return;
    glm::quat rotateQuat = glm::angleAxis(glm::radians((float) angle), axis);
    this->rotation       = glm::normalize(rotateQuat * this->rotation);
    this->updateView();
}

void Camera::move(glm::vec3 vector)
{
    this->position += vector;
    this->updateView();
}

void Camera::updateView()
{
    this->view = glm::translate(glm::mat4(1.f), -position)
                 * static_cast<glm::mat4>(this->rotation);
}

const glm::mat4 &Camera::getView() const
{
    return this->view;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getRotation() const
{
    return glm::eulerAngles(rotation) * 180.f / 3.14159f;
}

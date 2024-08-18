#include "Camera.hpp"

#include <iostream>
#include <cmath>
#include "glm/gtx/vector_angle.hpp"

#include "CameraPosition.hpp"


Camera::Camera()
{
    this->updateView();
    motionTaskHandler = std::thread(&Camera::motionTask, this);
}

Camera::~Camera()
{
    exit = true;
    motionTaskHandler.join();
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

    std::lock_guard lock(cameraMotionMutex);
    cameraMotion.reset();

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

glm::quat Camera::getRotationQuad() const
{
    return rotation;
}

void Camera::setPosition(CameraPosition newPositino)
{
    if(newPositino.rotation) {
        glm::vec3 targetDirect = glm::normalize(*newPositino.rotation);
        glm::vec3 defaultDirect{0.f, 0.f, 1.f};
        glm::vec3 currentDir = glm::inverse(rotation) * defaultDirect;

        glm::vec3 roteteVector
        = glm::normalize(rotation * glm::cross(currentDir, targetDirect));
        auto angle = glm::angle(currentDir, targetDirect);

        if((angle > -0.001 && angle < 0.001)) return;

        std::lock_guard lock(cameraMotionMutex);
        cameraMotion               = std::make_optional<CameraMotion>();
        cameraMotion->rotateVector = roteteVector;
        cameraMotion->angle        = -angle;
        cameraMotion->progress     = 0;
    }
}


void Camera::motionTask()
{
    using namespace std::chrono_literals;
    while(!exit) {
        std::this_thread::sleep_for(20ms);
        if(!cameraMotion) continue;

        std::lock_guard lock(cameraMotionMutex);
        glm::quat rotateQuat
        = glm::angleAxis(cameraMotion->angle / 5, cameraMotion->rotateVector);

        this->rotation = rotateQuat * this->rotation;
        this->updateView();

        cameraMotion->progress += 0.2;
        if(cameraMotion->progress >= 1.0) {
            cameraMotion.reset();
        }
    }
}

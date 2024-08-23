#include "Camera.hpp"

#include <iostream>
#include "glm/log.hpp"
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

void Camera::setProjectonAspectRatio(float width, float height)
{
    if(height == 0) height = 1;
    float aspect             = width / height;
    static const float zNear = 1.0, zFar = 14.0, fov = 45.0;

    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    this->projectionOrtho
    = glm::ortho(0.f, width, 0.f, height, -width / 2, width / 2);
}

const glm::mat4 &Camera::getProjection() const
{
    return this->projection;
}

const glm::mat4 &Camera::getProjectionOrtho() const
{
    return this->projectionOrtho;
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

glm::mat4 Camera::getRotation() const
{
    return static_cast<glm::mat4>(rotation);
}

glm::vec3 Camera::getRotationEuler() const
{
    return glm::eulerAngles(rotation) * 180.f / 3.14159f;
}

glm::quat Camera::getRotationQuad() const
{
    return rotation;
}

float Camera::getAngleXY(glm::vec3 lhs, glm::vec3 rhs)
{
    return std::atan2(
    lhs.y * rhs.x - lhs.x * rhs.y, lhs.x * rhs.x + lhs.y * rhs.y);
}

float Camera::reductAngle(float angle, float max)
{
    while(angle > max / 2.f) angle -= max;
    while(angle < -max / 2.f) angle += max;
    return angle;
}

std::pair<glm::vec3, float> Camera::breakQuat(glm::quat quat)
{
    float cosHalf = quat.w;
    float angle   = std::acos(cosHalf) * 2;
    float sin     = std::sin(angle);
    glm::vec3 vec
    = glm::normalize(glm::vec3{quat.x / sin, quat.y / sin, quat.z / sin});

    return std::pair<glm::vec3, float>{vec, angle};
}

/*
q0 = cos(fi/2)
q1 = x * sin(fi/2)
q2 = y * sin(fi/2)
q3 = z * sin(fi/2)
*/
void Camera::setPosition(CameraPosition newPositino)
{
    std::lock_guard lock(cameraMotionMutex);

    glm::quat rot{1, 0, 0, 0};
    static glm::vec3 defaultDirect{0.f, 0.f, 1.f};
    static glm::vec3 topDirect{0.f, 1.f, 0.f};
    glm::vec3 currentDirect = glm::inverse(rotation) * defaultDirect;

    if(newPositino.rotation) {
        glm::vec3 targetDirect = glm::normalize(*newPositino.rotation);

        glm::vec3 roteteVector
        = glm::normalize(rotation * glm::cross(currentDirect, targetDirect));
        auto angle = -glm::angle(currentDirect, targetDirect);

        rot = glm::angleAxis(angle, roteteVector);
    }
    if(newPositino.alignRotation) {
        glm::vec3 targetDirect = newPositino.rotation
                                 ? glm::normalize(*newPositino.rotation)
                                 : currentDirect;
        glm::quat preStepRot   = rot * this->rotation;

        glm::mat3 xAxis{
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
        };
        glm::vec3 currentTopDir
        = glm::normalize(preStepRot * (xAxis * targetDirect));

        float angle = reductAngle(getAngleXY(topDirect, currentTopDir));

        glm::quat finalRot = glm::angleAxis(angle, (preStepRot * targetDirect));
        rot                = finalRot * rot;
    }

    if(rot != glm::quat{1, 0, 0, 0}) {
        cameraMotion = std::make_optional<CameraMotion>();

        auto [rotVec, rotAngle]    = breakQuat(rot);
        cameraMotion->angle        = rotAngle;
        cameraMotion->rotateVector = rotVec;
    }
}


void Camera::motionTask()
{
    using namespace std::chrono_literals;
    while(!exit) {
        std::this_thread::sleep_for(10ms);
        std::lock_guard lock(cameraMotionMutex);
        if(!cameraMotion) continue;

        if((cameraMotion->angle < -0.0001 || cameraMotion->angle > 0.0001)) {
            glm::quat rotateQuat = glm::angleAxis(
            cameraMotion->angle / 10, cameraMotion->rotateVector);

            this->rotation = rotateQuat * this->rotation;
            this->updateView();
        }

        cameraMotion->progress += 0.1;
        if(cameraMotion->progress >= 1.0) {
            cameraMotion.reset();
        }
    }
}

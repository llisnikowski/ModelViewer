#pragma once
#include <memory>
#include <optional>
#include <thread>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "CameraMotion.hpp"

struct CameraPosition;

class Camera
{
public:
    Camera();
    ~Camera();

    void setProjectonAspectRatio(double aspect);
    const glm::mat4 &getProjection() const;

    void rotate(glm::vec3 axis, double angle);
    void move(glm::vec3 vector);
    const glm::mat4 &getView() const;

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::quat getRotationQuad() const;

    void setPosition(CameraPosition newPositino);

private:
    void updateView();
    void motionTask();

    float getAngleXY(glm::vec3 lhs, glm::vec3 rhs);
    float reductAngle(float angle, float max = M_PI / 2.f);
    std::pair<glm::vec3, float> breakQuat(glm::quat quat);

    glm::mat4 projection{};
    glm::quat rotation{1, 0, 0, 0};
    glm::vec3 position{0.f, 0.f, 4};
    glm::mat4 view{};

    std::atomic<bool> exit{};
    std::thread motionTaskHandler;
    std::mutex cameraMotionMutex;
    std::optional<CameraMotion> cameraMotion;
};

#pragma once
#include "camera/Camera.hpp"
#include "glm/glm.hpp"
#include <memory>

struct GLFWwindow;

class CameraManager
{
public:
    static void mouseButtonCallback(
    GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double x, double y);
    static void scrollCallback(
    GLFWwindow* window, double xoffset, double yoffset);

    static void init();

    static std::unique_ptr<Camera> camera;

private:
    static glm::vec2 mousePressPosition;
    static bool rightButtonPress;
    static bool middleButtonPress;
};

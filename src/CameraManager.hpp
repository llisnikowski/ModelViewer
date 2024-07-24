#pragma once
#include "model/Camera.hpp"
#include "glm/glm.hpp"

struct GLFWwindow;

class CameraManager
{
public:
    static void cursorPositionCallback(GLFWwindow* window, double x, double y);
    static void mouseButtonCallback(
    GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(
    GLFWwindow* window, double xoffset, double yoffset);

    static Camera camera;

private:
    static glm::vec2 mousePressPosition;
    static bool rightButtonPress;
    static bool middleButtonPress;
};

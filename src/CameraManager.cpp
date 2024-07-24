#include "CameraManager.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>


Camera CameraManager::camera{};
glm::vec2 CameraManager::mousePressPosition{};

bool CameraManager::rightButtonPress{};
bool CameraManager::middleButtonPress{};

void CameraManager::cursorPositionCallback(
GLFWwindow* window, double x, double y)
{
    glm::vec2 diff{x - mousePressPosition.x, y - mousePressPosition.y};

    if(diff.x == 0 && diff.y == 0) return;
    mousePressPosition.x = x;
    mousePressPosition.y = y;

    if(rightButtonPress) {
        float sensitivity = 150;
        camera.move(-glm::vec3(diff.x, -diff.y, 0.f) / sensitivity);
    }
    if(middleButtonPress) {
        glm::vec3 rotationAxis = glm::normalize(glm::vec3(diff.y, diff.x, 0.0));

        float sensitivity = 1;
        camera.rotate(rotationAxis, sensitivity);
    }
}

void CameraManager::mouseButtonCallback(
GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        mousePressPosition.x = x;
        mousePressPosition.y = y;

        if(button == GLFW_MOUSE_BUTTON_RIGHT) {
            rightButtonPress = true;
        }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE) {
            middleButtonPress = true;
        }
        return;
    }
    if(action == GLFW_RELEASE) {
        if(button == GLFW_MOUSE_BUTTON_RIGHT) {
            rightButtonPress = false;
        }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE) {
            middleButtonPress = false;
        }
        return;
    }
}

void CameraManager::scrollCallback(
GLFWwindow* window, double xoffset, double yoffset)
{
    glm::vec2 mousePosition;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    mousePosition.x = x;
    mousePosition.y = y;

    glm::vec3 moveDir = glm::vec3(0.f, 0.f, -1.f * yoffset / 10.0);
    camera.move(moveDir);
}

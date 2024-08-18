#include "imgui.h"
#include <glad/glad.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <GLFW/glfw3.h>
#include <llgl/Llgl.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <llgl/ImguiSetup.hpp>
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include "model/Model.hpp"

#include "CameraManager.hpp"

#include "Controller.hpp"
#include "Menu.hpp"
#include "reference/MainAxis.hpp"
#include "reference/RefCube.hpp"

#include "reycast/Picking.hpp"

#include "dataTemplates/ShadersManager.hpp"


void resizeWindowCallback(GLFWwindow* window, int width, int height);
llgl::Size windowSize{1280, 720};

struct MousePosition
{
    int x;
    int y;
};

MousePosition mouseInfo;
MousePosition leftButtonClickInfo;

void rightButtonClickCallback();

void cursorPositionCallback(GLFWwindow* window, double x, double y);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

std::unique_ptr<RefCube> refCube;
std::unique_ptr<Picking> picking;

int main(int argc, char* argv[])
{
    std::unique_ptr<llgl::Llgl> llgl;
    std::unique_ptr<llgl::ImguiSetup> imguiSetup;

    try {
        llgl       = std::make_unique<llgl::Llgl>("Cad", windowSize);
        imguiSetup = std::make_unique<llgl::ImguiSetup>(llgl->getWindow());
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    CameraManager::init();

    CameraManager::camera->setProjectonAspectRatio(
    float(windowSize.width) / float(windowSize.height ? windowSize.height : 1));


    Controller controller{};
    Menu menu{controller, windowSize};

    ShaderManager shaderManager;
    picking = std::make_unique<Picking>(
    llgl::Size{windowSize.width, windowSize.height});

    Model model;

    MainAxis mainAxis;
    refCube = std::make_unique<RefCube>(*CameraManager::camera);

    picking->addObject(refCube.get());

    glfwSetFramebufferSizeCallback(llgl->getWindow(), resizeWindowCallback);

    glfwSetCursorPosCallback(llgl->getWindow(), cursorPositionCallback);
    glfwSetMouseButtonCallback(llgl->getWindow(), mouseButtonCallback);
    glfwSetScrollCallback(llgl->getWindow(), scrollCallback);

    while(glfwWindowShouldClose(llgl->getWindow()) == 0) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        menu.draw();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, windowSize.width, windowSize.height);
        glClearColor(0.45F, 0.55F, 0.60F, 1.00F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glEnable(GL_DEPTH_TEST);
        {
            auto shader = shaderManager.getPicking();
            shader->bind();
            shader->getUniform("mvp").setMat4(
            CameraManager::camera->getProjection()
            * CameraManager::camera->getView());
            picking->check(
            shader, mouseInfo.x, windowSize.height - mouseInfo.y - 1);
        }

        {
            auto shader = shaderManager.getSimple();
            shader->bind();
            shader->getUniform("mvp").setMat4(
            CameraManager::camera->getProjection()
            * CameraManager::camera->getView());
            refCube->draw(shader);
            // model.draw(shader);
        }

        {
            glLineWidth(2);
            glDisable(GL_DEPTH_TEST);
            auto shader = shaderManager.getSimpleColor();
            shader->bind();
            shader->getUniform("mvp").setMat4(
            CameraManager::camera->getProjection()
            * CameraManager::camera->getView());
            mainAxis.draw();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(llgl->getWindow());
    }


    return 0;
}

void resizeWindowCallback(GLFWwindow* window, int width, int height)
{
    windowSize.width  = width;
    windowSize.height = height;

    CameraManager::camera->setProjectonAspectRatio(
    float(width) / float(height ? height : 1));

    picking->setWindowSize(windowSize);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);
    if(io.WantCaptureMouse) return;

    CameraManager::mouseButtonCallback(window, button, action, mods);



    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS) {
            leftButtonClickInfo.x = mouseInfo.x;
            leftButtonClickInfo.y = mouseInfo.y;
        }
        else if(action == GLFW_RELEASE) {
            if(mouseInfo.x > leftButtonClickInfo.x - 5
               && mouseInfo.x < leftButtonClickInfo.x + 5
               && mouseInfo.y > leftButtonClickInfo.y - 5
               && mouseInfo.y < leftButtonClickInfo.y + 5)
            {
                rightButtonClickCallback();
            }
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
    mouseInfo.x = x;
    mouseInfo.y = y;

    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(x, y);

    if(io.WantSetMousePos) {
        return;
    }

    CameraManager::cursorPositionCallback(window, x, y);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseWheelEvent(xoffset, yoffset);

    CameraManager::scrollCallback(window, xoffset, yoffset);
}

void rightButtonClickCallback()
{
    refCube->click();
}

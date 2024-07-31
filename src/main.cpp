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
#include "model/Model.hpp"

#include "CameraManager.hpp"

#include "Controller.hpp"
#include "Menu.hpp"
#include "reference/MainAxis.hpp"

void resizeWindowCallback(GLFWwindow* window, int width, int height);
llgl::Size windowSize{1280, 720};

void cursorPositionCallback(GLFWwindow* window, double x, double y);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


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

    CameraManager::camera.setProjectonAspectRatio(
    float(windowSize.width) / float(windowSize.height ? windowSize.height : 1));


    Controller controller{};
    Menu menu{controller, windowSize};

    Model model{CameraManager::camera};

    MainAxis mainAxis{CameraManager::camera};

    glfwSetFramebufferSizeCallback(llgl->getWindow(), resizeWindowCallback);

    glfwSetCursorPosCallback(llgl->getWindow(), cursorPositionCallback);
    glfwSetMouseButtonCallback(llgl->getWindow(), mouseButtonCallback);
    glfwSetScrollCallback(llgl->getWindow(), scrollCallback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

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

        glLineWidth(2);

        model.draw();
        mainAxis.draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(llgl->getWindow());
    }


    return 0;
}

void resizeWindowCallback(GLFWwindow* window, int width, int height)
{
    windowSize.width  = width;
    windowSize.height = height;

    CameraManager::camera.setProjectonAspectRatio(
    float(width) / float(height ? height : 1));
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);
    if(io.WantCaptureMouse) return;

    CameraManager::mouseButtonCallback(window, button, action, mods);
}

void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
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

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


void cursorPositionCallback(GLFWwindow* window, double x, double y);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


int main(int argc, char* argv[])
{
    std::unique_ptr<llgl::Llgl> llgl;
    std::unique_ptr<llgl::ImguiSetup> imguiSetup;

    try {
        llgl       = std::make_unique<llgl::Llgl>("Cad", llgl::Size{1280, 720});
        imguiSetup = std::make_unique<llgl::ImguiSetup>(llgl->getWindow());
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    enum class Mode
    {
        NORMAL,
        DRAW,
    };
    Mode mode{Mode::NORMAL};

    enum class DrawFigure
    {
        NONE,
        LINE,
    };

    DrawFigure drawFigure{};

    ImGuiStyle* style            = &ImGui::GetStyle();
    style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    Model model{CameraManager::camera};

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

        int display_w{};
        int display_h{};
        glfwGetFramebufferSize(llgl->getWindow(), &display_w, &display_h);
        CameraManager::camera.setProjectonAspectRatio(
        float(display_w) / float(display_h ? display_h : 1));

        if(mode == Mode::NORMAL) {
            ImGui::SetNextWindowPos(ImVec2{0, 0});
            ImGui::SetNextWindowSize(ImVec2{200, (float) display_h});
            ImGui::Begin("Operation");

            if(ImGui::Button("Draw")) {
                mode       = Mode::DRAW;
                drawFigure = DrawFigure::NONE;
            }

            auto pos = CameraManager::camera.getPosition();
            auto rot = CameraManager::camera.getRotation();

            ImGui::Text("Position");
            ImGui::Text("[%.3f, %.3f, %.3f]", pos.x, pos.y, pos.z);
            ImGui::Text("Rotation");
            ImGui::Text("[%.3f, %.3f, %.3f]", rot.x, rot.y, rot.z);

            ImGui::End();
        }

        if(mode == Mode::DRAW) {
            ImGui::SetNextWindowPos(ImVec2{0, 0});
            ImGui::SetNextWindowSize(ImVec2{200, (float) display_h});
            ImGui::Begin("Draw");

            if(ImGui::Button("Exit draw")) {
                mode = Mode::NORMAL;
            }

            if(drawFigure == DrawFigure::LINE) {
                ImGui::PushStyleColor(
                ImGuiCol_Button, IM_COL32(0, 255, 0, 255));

                if(ImGui::Button("Line")) {
                    drawFigure = DrawFigure::NONE;
                }
                ImGui::PopStyleColor();
            }
            else {
                if(ImGui::Button("Line")) {
                    drawFigure = DrawFigure::LINE;
                }
            }

            switch(drawFigure) {
            case DrawFigure::LINE: ImGui::Text("Draw Line"); break;
            case DrawFigure::NONE: break;
            }

            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45F, 0.55F, 0.60F, 1.00F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLineWidth(2);

        model.draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(llgl->getWindow());
    }


    return 0;
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

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
#include "model/SimpleCube.hpp"

#include "CameraManager.hpp"
#include "camera/CameraPosition.hpp"

#include "Controller.hpp"
#include "Menu.hpp"
#include "reference/MainAxis.hpp"
#include "reference/RefCube.hpp"
#include "reference/NaviIcons.hpp"

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
std::array<std::unique_ptr<NaviIcons>, 2> naviIcons; // left, right
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
    float(windowSize.width), float(windowSize.height));


    Controller controller{};
    Menu menu{controller, windowSize};

    ShaderManager shaderManager;
    picking = std::make_unique<Picking>(
    llgl::Size{windowSize.width, windowSize.height});

    SimpleCube simplecube;

    MainAxis mainAxis;
    refCube      = std::make_unique<RefCube>(*CameraManager::camera);
    naviIcons[0] = std::make_unique<NaviIcons>([] {
        glm::vec3 pos{-0.6f, 0.3f, 1.f};

        CameraPosition newPositino;
        newPositino.setAxisRotation(-M_PI / 2);
        CameraManager::camera->setPosition(newPositino);
    });
    naviIcons[1] = std::make_unique<NaviIcons>([] {
        glm::vec3 pos{-0.6f, 0.3f, 1.f};

        CameraPosition newPositino;
        newPositino.setAxisRotation(M_PI / 2);
        CameraManager::camera->setPosition(newPositino);
    });


    glfwSetFramebufferSizeCallback(llgl->getWindow(), resizeWindowCallback);

    glfwSetCursorPosCallback(llgl->getWindow(), cursorPositionCallback);
    glfwSetMouseButtonCallback(llgl->getWindow(), mouseButtonCallback);
    glfwSetScrollCallback(llgl->getWindow(), scrollCallback);

    PickingObject* lastPickingObject{};

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


        glm::mat4 mvpRefCube
        = CameraManager::camera->getProjectionOrtho()
          * glm::translate(glm::mat4(1.f),
          glm::vec3{windowSize.width - 100, windowSize.height - 100, 0})
          * CameraManager::camera->getRotation()
          * glm::scale(glm::mat4{1}, glm::vec3{60, 60, 60});

        std::array<glm::vec3, 2> naviIconsPosition{
        glm::vec3{ windowSize.width - 50, windowSize.height - 50, 0},
        glm::vec3{windowSize.width - 150, windowSize.height - 50, 0}
        };

        std::array<glm::mat4, 2> mvpNaviIcons;
        for(int i = 0; i < 2; i++) {
            mvpNaviIcons[i]
            = CameraManager::camera->getProjectionOrtho()
              * glm::translate(glm::mat4(1.f), naviIconsPosition[i])
              * glm::scale(glm::mat4{1}, glm::vec3{20, 20, 20});
        }

        glEnable(GL_DEPTH_TEST);
        {
            auto shader = shaderManager.getPicking();
            picking->startCheck(shader);
            picking->drawObject(1, refCube.get(), mvpRefCube);
            for(int i = 0; i < 2; i++) {
                picking->drawObject(2 + i, naviIcons[i].get(), mvpNaviIcons[i]);
            }
            Picking::PixelInfo pixel = picking->endCheck(
            mouseInfo.x, windowSize.height - mouseInfo.y - 1);

            PickingObject* pickingObject{};
            switch(pixel.objectID) {
            case 1: pickingObject = refCube.get(); break;
            case 2 + 0: pickingObject = naviIcons[0].get(); break;
            case 2 + 1:
                pickingObject = naviIcons[1].get();
                break;
                break;
            case 0:
            [[likely]]
            default:
                break;
            }

            if(pickingObject) {
                pickingObject->mouseEntered(pixel.primID);
                if(lastPickingObject && pickingObject != lastPickingObject) {
                    lastPickingObject->mouseExited();
                }
                lastPickingObject = pickingObject;
            }
            else if(lastPickingObject) {
                lastPickingObject->mouseExited();
                lastPickingObject = nullptr;
            }
        }

        {
            auto shader = shaderManager.getSimple();
            shader->bind();

            shader->getUniform("mvp").setMat4(
            CameraManager::camera->getProjection()
            * CameraManager::camera->getView());
            simplecube.draw(shader);

            shader->getUniform("mvp").setMat4(mvpRefCube);
            refCube->draw(shader);
        }


        {
            auto shader = shaderManager.getSimple();
            shader->bind();

            for(int i = 0; i < 2; i++) {
                shader->getUniform("mvp").setMat4(mvpNaviIcons[i]);

                naviIcons[i]->draw(shader);
            }
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

    CameraManager::camera->setProjectonAspectRatio(float(width), float(height));

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
    for(int i = 0; i < 2; i++) {
        naviIcons[i]->click();
    }
}

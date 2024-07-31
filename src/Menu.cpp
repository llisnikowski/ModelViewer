#include "Menu.hpp"
#include "Controller.hpp"
#include "llgl/Size.hpp"
#include "CameraManager.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


Menu::Menu(Controller &controller, llgl::Size &windowSize)
: controller{controller}
, windowSize{windowSize}
{}

Menu::~Menu() = default;

void Menu::draw()
{
    ImGui::SetNextWindowPos(ImVec2{0, 0});
    ImGui::SetNextWindowSize(ImVec2{200, (float) windowSize.height});
    if(controller.getMode() == Controller::Mode::NORMAL) {
        ImGui::Begin("Operation");
        drawNormal();
        ImGui::End();
    }
    else if(controller.getMode() == Controller::Mode::DRAW) {
        ImGui::Begin("Draw");
        drawDraw();
        ImGui::End();
    }
}

void Menu::drawNormal()
{
    if(ImGui::Button("Draw")) {
        controller.setMode(Controller::Mode::DRAW);
        // controller.setDrawFigure(DrawFigure::NONE);
    }

    auto pos = CameraManager::camera.getPosition();
    auto rot = CameraManager::camera.getRotation();

    ImGui::Text("Position");
    ImGui::Text("[%.3f, %.3f, %.3f]", pos.x, pos.y, pos.z);
    ImGui::Text("Rotation");
    ImGui::Text("[%.3f, %.3f, %.3f]", rot.x, rot.y, rot.z);
}

void Menu::drawDraw()
{
    if(ImGui::Button("Exit draw")) {
        controller.setMode(Controller::Mode::NORMAL);
    }

    if(controller.getDrawFigure() == Controller::DrawFigure::LINE) {
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 255, 0, 255));

        if(ImGui::Button("Line")) {
            controller.setDrawFigure(Controller::DrawFigure::NONE);
        }
        ImGui::PopStyleColor();
    }
    else {
        if(ImGui::Button("Line")) {
            controller.setDrawFigure(Controller::DrawFigure::LINE);
        }
    }

    switch(controller.getDrawFigure()) {
    case Controller::DrawFigure::LINE: ImGui::Text("Draw Line"); break;
    case Controller::DrawFigure::NONE: break;
    }
}

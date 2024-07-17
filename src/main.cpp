#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <GLFW/glfw3.h>
#include <llgl/Llgl.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <llgl/ImguiSetup.hpp>


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

    while(glfwWindowShouldClose(llgl->getWindow()) == 0) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int display_w{};
        int display_h{};
        glfwGetFramebufferSize(llgl->getWindow(), &display_w, &display_h);


        if(mode == Mode::NORMAL) {
            ImGui::SetNextWindowPos(ImVec2{0, 0});
            ImGui::SetNextWindowSize(ImVec2{200, (float) display_h});
            ImGui::Begin("Operation");

            if(ImGui::Button("Draw")) {
                mode       = Mode::DRAW;
                drawFigure = DrawFigure::NONE;
            }

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
                    if(drawFigure != DrawFigure::LINE) {
                        drawFigure = DrawFigure::LINE;
                    }
                    else {
                        drawFigure = DrawFigure::NONE;
                    }
                }
                ImGui::PopStyleColor();
            }
            else {
                if(ImGui::Button("Line")) {
                    if(drawFigure != DrawFigure::LINE) {
                        drawFigure = DrawFigure::LINE;
                    }
                    else {
                        drawFigure = DrawFigure::NONE;
                    }
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
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(llgl->getWindow());
    }


    return 0;
}

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <GLFW/glfw3.h>



int main(int argc, char* argv[])
{
    if(glfwInit() == 0) {
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);


    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(
    1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if(window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags
    |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags
    |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);




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

    while(glfwWindowShouldClose(window) == 0) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int display_w{};
        int display_h{};
        glfwGetFramebufferSize(window, &display_w, &display_h);


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

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

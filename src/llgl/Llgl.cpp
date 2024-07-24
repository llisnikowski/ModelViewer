#include "llgl/Llgl.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdexcept>


namespace llgl
{

Llgl::Llgl(std::string name, Size size)
: Window{std::move(name), size}
{
    init();
}

Llgl::Llgl()
: Window{}
{}

Llgl::~Llgl()
{
    glfwTerminate();
}

void Llgl::init()
{
    this->glfwInit();
    this->Window::init();
    gladLoadGL();
}

void Llgl::glfwInit()
{
    if(::glfwInit() == 0) throw std::runtime_error{"glfwInit error"};
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Llgl::run()
{
    if(Window::getWindow() == nullptr) return;

    while(!glfwWindowShouldClose(Window::getWindow())) {
        const Color &color = this->Window::getBackgroundColor();
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // objectLock->draw();

        glfwSwapBuffers(Window::getWindow());
        glfwPollEvents();
    }
}

} // namespace llgl

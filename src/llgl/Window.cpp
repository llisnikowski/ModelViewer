#include "llgl/Window.hpp"

#ifdef USE_GLAD
#    include "glad/glad.h"
#elif defined(USE_IMGUI)
#    include "imgui.h"
#    include "imgui_impl_glfw.h"
#    include "imgui_impl_opengl3.h"
#else
#    error "you DON'T using glad"
#endif
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace llgl
{

Window::Window(std::string name, Size size)
: name{std::move(name)}
, size{size}
, color{1.0, 1.0, 1.0}
, window{nullptr}
{}

Window::Window()
: name{}
, size{}
, color{}
, window{nullptr}
{}

Window::~Window()
{
    if(this->window) {
        glfwDestroyWindow(this->window);
        this->window = nullptr;
    }
}

void Window::init()
{
    if(size.width <= 0 || size.height <= 0)
        throw std::invalid_argument{"Invalid window size"};
    this->window
    = glfwCreateWindow(size.width, size.height, name.c_str(), nullptr, nullptr);
    if(this->window == nullptr) throw std::runtime_error{"create window error"};
    ;

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
}


std::string Window::getName() const
{
    return this->name;
}

Size Window::getSize() const
{
    return this->size;
}

void Window::setSize(Size size)
{
    this->size = size;
}

void Window::setName(std::string name)
{
    this->name = name;
}

Color Window::getBackgroundColor() const
{
    return this->color;
}

void Window::setBackgroundColor(Color color)
{
    this->color = color;
}



} // namespace llgl

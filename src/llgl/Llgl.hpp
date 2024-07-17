#pragma once
#include "llgl/Window.hpp"

namespace llgl
{

class Llgl : public Window
{
public:
    Llgl(std::string name, Size size);
    Llgl();
    ~Llgl();

    void run();

private:
    void init();
    void glfwInit();
};

} // namespace llgl

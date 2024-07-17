#pragma once

struct GLFWwindow;


namespace llgl
{

class ImguiSetup
{
public:
    ImguiSetup(GLFWwindow *window);
    ~ImguiSetup();
};

} // namespace llgl

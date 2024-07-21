#pragma once

struct GLFWwindow;


namespace llgl
{

class ImguiSetup
{
public:
    explicit ImguiSetup(GLFWwindow *window);
    ~ImguiSetup();
};

} // namespace llgl

#pragma once
#include <string>
#include "llgl/Size.hpp"
#include "llgl/Color.hpp"

struct GLFWwindow;

namespace llgl
{

class Window
{
public:
    Window(std::string name, Size size);
    Window();
    virtual ~Window();

    std::string getName() const;
    void setName(const std::string &name);
    void setName(std::string &&name);
    Size getSize() const;
    void setSize(Size size);
    Color getBackgroundColor() const;
    void setBackgroundColor(Color color);

    GLFWwindow *getWindow() { return this->window; }
protected:
    void init();

private:
    std::string name;
    Size size;
    Color color;
    GLFWwindow *window;
};

} // namespace llgl

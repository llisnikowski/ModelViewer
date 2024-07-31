#pragma once
#include <string>
#include <functional>
#include <vector>

class Controller;
namespace llgl
{
struct Size;
}

class Menu
{
public:
    Menu(Controller &controller, llgl::Size &windowSize);
    ~Menu();

    void draw();

private:
    void drawNormal();
    void drawDraw();

    using ItStr = std::vector<std::string>::const_iterator;
    void drawBranch(ItStr begin, ItStr end, std::function<void()> func);
    void drawTree();

    Controller &controller;
    llgl::Size &windowSize;
};

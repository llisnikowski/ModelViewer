#pragma once

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

    Controller &controller;
    llgl::Size &windowSize;
};

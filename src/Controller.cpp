#include "Controller.hpp"

void Controller::setMode(Mode mode)
{
    this->mode = mode;
}

Controller::Mode Controller::getMode() const
{
    return this->mode;
}

void Controller::setDrawFigure(DrawFigure drawFigure)
{
    this->drawFigure = drawFigure;
}

Controller::DrawFigure Controller::getDrawFigure() const
{
    return this->drawFigure;
}

Controller::Controller()
{
    modelView.emplace_back("Origin", "Origin");
    modelView.emplace_back(std::vector<std::string>{"Origin", "Plane"}, "X");
    modelView.emplace_back(std::vector<std::string>{"Origin", "Plane"}, "Y");
    modelView.emplace_back(std::vector<std::string>{"Origin", "Plane"}, "Z");
}

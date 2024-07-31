#pragma once
#include <vector>
#include <ModelView.hpp>


class Controller
{
public:
    Controller();

    enum class Mode
    {
        NORMAL,
        DRAW,
    };
    void setMode(Mode mode);
    Mode getMode() const;
private:
    Mode mode{Mode::NORMAL};

public:
    enum class DrawFigure
    {
        NONE,
        LINE,
    };
    void setDrawFigure(DrawFigure drawFigure);
    DrawFigure getDrawFigure() const;
private:
    DrawFigure drawFigure{};

public:
    std::vector<ModelView> modelView;
};

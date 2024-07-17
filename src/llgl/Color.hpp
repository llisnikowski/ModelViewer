#pragma once
#include <stdint.h>

namespace llgl
{

class Color
{
public:
    constexpr Color(float r = 0, float g = 0, float b = 0);

    static constexpr Color white();
    static constexpr Color black();
    static constexpr Color red();
    static constexpr Color green();
    static constexpr Color blue();

    float r;
    float g;
    float b;
};


//-----------------------

constexpr Color::Color(float r, float g, float b)
: r{r}
, g{g}
, b{b}
{}

constexpr Color Color::white()
{
    return Color(1.0f, 1.0f, 1.0f);
}
constexpr Color Color::black()
{
    return Color(0.0f, 0.0f, 0.0f);
}
constexpr Color Color::red()
{
    return Color(1.0f, 0.0f, 0.0f);
}
constexpr Color Color::green()
{
    return Color(0.0f, 1.0f, 0.0f);
}
constexpr Color Color::blue()
{
    return Color(0.0f, 0.0f, 1.0f);
}


} // namespace llgl

constexpr bool operator==(llgl::Color rhs, llgl::Color lhs)
{
    return rhs.r == lhs.r && rhs.g == lhs.g && rhs.b == lhs.b;
}

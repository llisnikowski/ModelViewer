#pragma once
#include <cstddef>

namespace llgl
{

struct Size
{
    constexpr Size(int width, int height);
    constexpr explicit Size(int size);
    constexpr Size();

    int width;
    int height;
};


//-----------------------

constexpr Size::Size(int width, int height)
: width{width}
, height{height}
{}

constexpr Size::Size(int size)
: width{size}
, height{size}
{}

constexpr Size::Size()
: width{0}
, height{0}
{}


} // namespace llgl

constexpr bool operator==(llgl::Size rhs, llgl::Size lhs)
{
    return rhs.width == lhs.width && rhs.height == lhs.height;
}

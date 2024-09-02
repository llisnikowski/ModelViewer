#pragma once
#include <memory>
#include "reycast/Picking.hpp"


namespace llgl
{
class VertexArray;
class VertexBuffer;
class ElementBuffer;
class ShaderProgram;
}
class Camera;


class NaviIcons : public PickingObject
{
public:
    NaviIcons(Camera &camera);
    ~NaviIcons();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);
    void drawPicking() override;

    void mouseEntered(unsigned int primID) override;
    void mouseExited() override;

    void click();

private:
    void init();

    struct
    {
        unsigned int primID{};
        bool mouseEnter = false;
    } mouseState;

    int elementsCount{};

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;

    Camera &camera;
};

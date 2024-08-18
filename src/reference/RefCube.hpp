#pragma once
#include <array>
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

class RefCube : public PickingObject
{
public:
    explicit RefCube(Camera &camera);
    ~RefCube();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);
    void drawPicking() override;

    void mouseEntered(unsigned int primID) override;
    void mouseExited() override;

    void click();

private:
    void loadShader();
    void init();

    void initData();
    void initDataCube();

    int elementsCubeCount{};
    int elementsCubeEdgeCount{};

    struct
    {
        unsigned int primID{};
        bool mouseEnter = false;
    } mouseState;


    std::unique_ptr<llgl::VertexArray> vaoCube;
    std::shared_ptr<llgl::VertexBuffer> vboCube;
    std::shared_ptr<llgl::ElementBuffer> eboCube;

    std::unique_ptr<llgl::VertexArray> vaoCubeEdge;
    std::shared_ptr<llgl::ElementBuffer> eboCubeEdge;

    Camera &camera;
};

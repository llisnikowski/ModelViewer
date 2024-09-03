#pragma once
#include <array>
#include <memory>

namespace llgl
{
class VertexArray;
class VertexBuffer;
class ElementBuffer;
class ShaderProgram;
}

class SimpleCube
{
public:
    explicit SimpleCube();
    ~SimpleCube();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);

private:
    void loadShader();
    void init();

    void initData();

    int triangleCount{};
    int edgeCount{};

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;

    std::unique_ptr<llgl::VertexArray> vaoEdge;
    std::shared_ptr<llgl::ElementBuffer> eboEdge;
};

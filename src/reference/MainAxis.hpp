#pragma once
#include <array>
#include <memory>


namespace llgl
{
class VertexArray;
class VertexBuffer;
}

class MainAxis
{
public:
    explicit MainAxis();
    ~MainAxis();

    void draw();

private:
    void init();

    void initData();

    int lineCount{};

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
};

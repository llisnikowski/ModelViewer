#include "MainAxis.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include <iostream>


MainAxis::MainAxis()
{
    init();
}

MainAxis::~MainAxis() = default;

void MainAxis::draw()
{
    vao->bind();

    glDrawArrays(GL_LINES, 0, lineCount);
}

void MainAxis::init()
{
    initData();
}

void MainAxis::initData()
{
    vbo = std::make_shared<llgl::VertexBuffer>();

    struct VertexData
    {
        std::array<float, 3> pos;
        std::array<float, 3> color;
    };
    VertexData vertices[]{
    {  {0, 0, 0}, {1, 0, 0}},
    {{0.5, 0, 0}, {1, 0, 0}},
    {  {0, 0, 0}, {0, 1, 0}},
    {{0, 0.5, 0}, {0, 1, 0}},
    {  {0, 0, 0}, {0, 0, 1}},
    {{0, 0, 0.5}, {0, 0, 1}}
    };

    vbo->allocate(vertices, sizeof(vertices));

    lineCount = sizeof(vertices) / sizeof(VertexData);

    vao = std::make_unique<llgl::VertexArray>();
    vao->setAttrib<float>(0, 3, 6 * sizeof(float), 0, *vbo);
    vao->setAttrib<float>(1, 3, 6 * sizeof(float), 3 * sizeof(float), *vbo);
}

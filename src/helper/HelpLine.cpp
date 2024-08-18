#include "HelpLine.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>


HelpLine::HelpLine()
{
    init();
}

HelpLine::~HelpLine() = default;

void HelpLine::draw()
{
    vao->bind();

    glLineWidth(4);
    glDrawArrays(GL_LINES, 0, lineCount);
}

void HelpLine::init()
{
    initData();
}

void HelpLine::initData()
{
    vbo = std::make_shared<llgl::VertexBuffer>();

    struct VertexData
    {
        std::array<float, 3> pos;
    };
    VertexData vertices[]{{{0, 0, 0}}, {{1, 0, 0}}};

    vbo->allocate(vertices, sizeof(vertices));

    lineCount = sizeof(vertices) / sizeof(VertexData);

    vao = std::make_unique<llgl::VertexArray>();
    vao->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);
}

void HelpLine::setP2(glm::vec3 vec)
{
    struct VertexData
    {
        std::array<float, 3> pos;
    };

    VertexData vertices[]{{{0, 0, 0}}, {{vec.x, vec.y, vec.z}}};
    vbo->changeDate(vertices, sizeof(vertices));
}

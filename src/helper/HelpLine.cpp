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
    std::lock_guard lock{mutex};
    if(changeLine) {
        struct VertexData
        {
            std::array<float, 3> pos;
        };
        VertexData vertices[]{{{p1.x, p1.y, p1.z}}, {{p2.x, p2.y, p2.z}}};
        vbo->changeDate(vertices, sizeof(vertices));
        changeLine = false;
    }

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

void HelpLine::setP1(glm::vec3 vec)
{
    std::lock_guard lock{mutex};

    changeLine = true;
    p1         = vec;
}

void HelpLine::setP2(glm::vec3 vec)
{
    std::lock_guard lock{mutex};

    changeLine = true;
    p2         = vec;
}

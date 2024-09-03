#include "SimpleCube.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>
#include "dataTemplates/ExampleData.hpp"


SimpleCube::SimpleCube()
{
    init();
}

SimpleCube::~SimpleCube() = default;

void SimpleCube::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    vao->bind();

    ebo->bind();
    program->getUniform("color").setVec3(0.5f, 0.8f, 0.4f);
    glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_SHORT, nullptr);

    program->getUniform("color").setVec3(0.2f, 0.2f, 0.2f);
    eboEdge->bind();
    glDrawElements(GL_LINES, edgeCount, GL_UNSIGNED_SHORT, nullptr);
}

void SimpleCube::init()
{
    initData();
}

void SimpleCube::initData()
{
    vbo = std::make_shared<llgl::VertexBuffer>();
    vbo->allocate(cubeVertices, sizeof(cubeVertices));

    ebo = std::make_shared<llgl::ElementBuffer>();
    ebo->allocate(cubeIndices, sizeof(cubeIndices));

    triangleCount = sizeof(cubeIndices) / sizeof(unsigned short);

    vao = std::make_unique<llgl::VertexArray>();
    vao->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);

    eboEdge = std::make_shared<llgl::ElementBuffer>();
    eboEdge->allocate(edgeIndices, sizeof(edgeIndices));
    edgeCount = sizeof(edgeIndices) / sizeof(unsigned short);

    vaoEdge = std::make_unique<llgl::VertexArray>();
    vaoEdge->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);
}

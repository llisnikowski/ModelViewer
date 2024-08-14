#include "RefCube.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>

#include "dataTemplates/VertexData.hpp"
#include "dataTemplates/ExampleData.hpp"


RefCube::RefCube()
{
    init();
}

RefCube::~RefCube() = default;

void RefCube::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    program->getUniform("color").setVec3(0.6f, 0.6f, 0.9f);

    vaoCube->bind();
    eboCube->bind();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, nullptr);
    glDrawElements(GL_TRIANGLES, elementsCubeCount, GL_UNSIGNED_SHORT, nullptr);

    glLineWidth(1);
    program->getUniform("color").setVec3(0.2f, 0.2f, 0.2f);
    eboCubeEdge->bind();
    glDrawElements(GL_LINES, elementsCubeEdgeCount, GL_UNSIGNED_SHORT, nullptr);

    if(this->mouseState.mouseEnter) {
        program->getUniform("color").setVec3(0.7f, 0.7f, 1.0f);
        vaoCube->bind();
        eboCube->bind();
        glDisable(GL_DEPTH_TEST);
        glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
        reinterpret_cast<void *>(6 * (this->mouseState.primID / 2) * 2), 0);
    }
}

void RefCube::mouseEntered(unsigned int primID)
{
    this->mouseState.primID     = primID;
    this->mouseState.mouseEnter = true;
}

void RefCube::mouseExited()
{
    this->mouseState.mouseEnter = false;
}


void RefCube::drawPicking()
{
    vaoCube->bind();
    eboCube->bind();
    glDrawElements(GL_TRIANGLES, elementsCubeCount, GL_UNSIGNED_SHORT, nullptr);
}

void RefCube::init()
{
    initData();
}

void RefCube::initData()
{
    initDataCube();
}

void RefCube::initDataCube()
{
    vboCube = std::make_shared<llgl::VertexBuffer>();
    vboCube->allocate(cubeVertices, sizeof(cubeVertices));

    eboCube = std::make_shared<llgl::ElementBuffer>();
    eboCube->allocate(cubeIndices, sizeof(cubeIndices));

    elementsCubeCount = sizeof(cubeIndices) / sizeof(unsigned short);

    vaoCube = std::make_unique<llgl::VertexArray>();
    vaoCube->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vboCube);

    eboCubeEdge = std::make_shared<llgl::ElementBuffer>();
    eboCubeEdge->allocate(edgeIndices, sizeof(edgeIndices));
    elementsCubeEdgeCount = sizeof(edgeIndices) / sizeof(unsigned short);

    vaoCubeEdge = std::make_unique<llgl::VertexArray>();
    vaoCubeEdge->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vboCube);
}

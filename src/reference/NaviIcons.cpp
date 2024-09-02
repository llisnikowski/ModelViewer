#include "NaviIcons.hpp"

#include <iostream>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"


#include "dataTemplates/VertexData.hpp"
#include "dataTemplates/ExampleData.hpp"

#include "camera/Camera.hpp"
#include "camera/CameraPosition.hpp"

NaviIcons::NaviIcons(Camera &camera)
: camera{camera}
{
    init();
}

NaviIcons::~NaviIcons() = default;

void NaviIcons::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    vao->bind();
    ebo->bind();

    if(this->mouseState.mouseEnter) {
        program->getUniform("color").setVec3(0.7f, 0.7f, 1.0f);
    }
    else {
        program->getUniform("color").setVec3(0.6f, 0.6f, 0.9f);
    }

    glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, nullptr);
}

void NaviIcons::drawPicking()
{
    vao->bind();
    ebo->bind();

    glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, nullptr);
}

void NaviIcons::mouseEntered(unsigned int primID)
{
    this->mouseState.primID     = primID;
    this->mouseState.mouseEnter = true;
}

void NaviIcons::mouseExited()
{
    this->mouseState.mouseEnter = false;
}

void NaviIcons::click()
{
    if(!this->mouseState.mouseEnter) return;

    glm::vec3 pos{-0.6f, 0.3f, 1.f};


    CameraPosition newPositino;
    newPositino.setRotation(pos);
    camera.setPosition(newPositino);
}


void NaviIcons::init()
{
    vbo = std::make_shared<llgl::VertexBuffer>();
    vbo->allocate(squareVertices, sizeof(squareVertices));

    ebo = std::make_shared<llgl::ElementBuffer>();
    ebo->allocate(squareIndices, sizeof(squareIndices));
    elementsCount = sizeof(squareIndices) / sizeof(unsigned short);

    vao = std::make_unique<llgl::VertexArray>();
    vao->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);
}

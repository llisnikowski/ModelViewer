#include "Model.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/Shader.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>
#include "Camera.hpp"
#include "ShadersTemplate.hpp"
#include "ExampleData.hpp"


Model::Model(Camera &camera)
: camera{camera}
{
    init();
}

Model::~Model() = default;

void Model::draw()
{
    vao->bind();
    program->bind();
    program->getUniform("mvp").setMat4(
    camera.getProjection() * camera.getView());

    ebo->bind();
    program->getUniform("color").setVec3(0.5f, 0.8f, 0.4f);
    glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_SHORT, nullptr);

    program->getUniform("color").setVec3(0.2f, 0.2f, 0.2f);
    eboEdge->bind();
    glDrawElements(GL_LINES, edgeCount, GL_UNSIGNED_SHORT, nullptr);
}

void loadShader() {}

void Model::init()
{
    initData();
    initProgram();
}

void Model::initData()
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

void Model::initProgram()
{
    try {
        vertexShader
        = std::make_shared<llgl::Shader>(simpleVS, llgl::Shader::Type::VERTEX);
        fragmentShader = std::make_shared<llgl::Shader>(
        simpleFS, llgl::Shader::Type::FRAGMENT);
    }
    catch(std::invalid_argument &ex) {
        std::cout << ex.what() << std::endl;
    }

    program = std::make_unique<llgl::ShaderProgram>();
    program->addShader(*vertexShader);
    program->addShader(*fragmentShader);
    program->link();
}

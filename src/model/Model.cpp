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
    ebo->bind();
    program->bind();
    program->getUniform("mvp").setMat4(
    camera.getProjection() * camera.getView());
    glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_SHORT, nullptr);
}

void loadShader() {}

void Model::init()
{
    try {
        vertexShader
        = std::make_shared<llgl::Shader>(simpleVS, llgl::Shader::Type::VERTEX);
    }
    catch(std::invalid_argument &ex) {
        std::cout << ex.what() << std::endl;
    }

    fragmentShader
    = std::make_shared<llgl::Shader>(simpleFS, llgl::Shader::Type::FRAGMENT);

    program = std::make_unique<llgl::ShaderProgram>();
    program->addShader(*vertexShader);
    program->addShader(*fragmentShader);
    program->link();


    triangleCount = sizeof(cubeIndices) / sizeof(unsigned short);

    vao = std::make_unique<llgl::VertexArray>();
    vbo = std::make_shared<llgl::VertexBuffer>();
    ebo = std::make_shared<llgl::ElementBuffer>();

    vbo->allocate(cubeVertices, sizeof(cubeVertices));
    ebo->allocate(cubeIndices, sizeof(cubeIndices));

    vao->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);

    ebo->bind();
    program->bind();
}

#include "MainAxis.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/Shader.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>
#include "camera/Camera.hpp"
#include "dataTemplates/ShadersTemplate.hpp"


MainAxis::MainAxis(Camera &camera)
: camera{camera}
{
    init();
}

MainAxis::~MainAxis() = default;

void MainAxis::draw()
{
    vao->bind();
    program->bind();
    program->getUniform("mvp").setMat4(
    camera.getProjection() * camera.getView());

    glDrawArrays(GL_LINES, 0, lineCount);
}

void MainAxis::init()
{
    initData();
    initProgram();
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

void MainAxis::initProgram()
{
    try {
        vertexShader = std::make_shared<llgl::Shader>(
        posAndColorVs, llgl::Shader::Type::VERTEX);
        fragmentShader
        = std::make_shared<llgl::Shader>(colorFs, llgl::Shader::Type::FRAGMENT);
    }
    catch(std::invalid_argument &ex) {
        std::cout << "shader error: " << ex.what() << std::endl;
    }

    program = std::make_unique<llgl::ShaderProgram>();
    program->addShader(*vertexShader);
    program->addShader(*fragmentShader);
    program->link();
}

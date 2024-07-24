#include "Model.hpp"

#include <memory>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/Shader.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"
#include <iostream>

Model::Model()
{
    init();
}

Model::~Model() = default;

void Model::draw()
{
    vao->bind();
    ebo->bind();
    program->bind();
    program->getUniform("position").setVec2(0.4, 0.2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void loadShader() {}

void Model::init()
{
    try {
        vertexShader = std::make_shared<llgl::Shader>(
        R"--|shader|--(#version 450 core
layout (location = 0) in vec3 aPos;

uniform vec2 position;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(position, 0, 0);
}
)--|shader|--",
        llgl::Shader::Type::VERTEX);
    }
    catch(std::invalid_argument &ex) {
        std::cout << ex.what() << std::endl;
    }

    fragmentShader = std::make_shared<llgl::Shader>(
    R"--|shader|--(#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)--|shader|--",
    llgl::Shader::Type::FRAGMENT);

    program = std::make_unique<llgl::ShaderProgram>();
    program->addShader(*vertexShader);
    program->addShader(*fragmentShader);
    program->link();


    VertexData vertices[]{
    { 0.5f,  0.5f, 0.0f}, // top right
    { 0.5f, -0.5f, 0.0f}, // bottom right
    {-0.5f, -0.5f, 0.0f}, // bottom left
    {-0.5f,  0.5f, 0.0f}  // top left
    };

    GLushort indices[] = {
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
    };

    triangleCount = sizeof(indices) / sizeof(GLushort);

    vao = std::make_unique<llgl::VertexArray>();
    vbo = std::make_shared<llgl::VertexBuffer>();
    ebo = std::make_shared<llgl::ElementBuffer>();

    vbo->allocate(vertices, sizeof(vertices));
    ebo->allocate(indices, sizeof(indices));

    vao->setAttrib<float>(0, 3, 3 * sizeof(float), 0, *vbo);

    ebo->bind();
    program->bind();
}

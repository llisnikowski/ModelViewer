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
    glDrawElements(
    GL_TRIANGLE_STRIP, triangleCount, GL_UNSIGNED_SHORT, nullptr);
}

void loadShader() {}

void Model::init()
{
    try {
        vertexShader = std::make_shared<llgl::Shader>(
        R"--|shader|--(#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main()
{
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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
    // { 0.5f,  0.5f, 0.0f}, // top right
    // { 0.5f, -0.5f, 0.0f}, // bottom right
    // {-0.5f, -0.5f, 0.0f}, // bottom left
    // {-0.5f,  0.5f, 0.0f}  // top left

    // Vertex data for face 0
    {-0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
    // Vertex data for face 1
    { 0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f, -0.5f},
    // Vertex data for face 2
    { 0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    // Vertex data for face 3
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f,  0.5f},
    // Vertex data for face 4
    {-0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f},
    // Vertex data for face 5
    {-0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
    {-0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f}
    };

    GLushort indices[] = {
    // 0, 1, 3, // first Triangle
    // 1, 2, 3  // second Triangle

    0, 1, 2, 3, 3,          // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4, 4, 5, 6, 7, 7,       // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8, 8, 9, 10, 11, 11,    // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
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

#include "Mesh.hpp"

#include <iostream>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices  = indices;

    setupMesh();
}

Mesh::Mesh(Mesh&& rhs)
{
    this->vertices = std::move(rhs.vertices);
    this->indices  = std::move(rhs.indices);

    this->vao = std::move(rhs.vao);
    this->vbo = std::move(rhs.vbo);
    this->ebo = std::move(rhs.ebo);
}

Mesh::~Mesh() = default;

void Mesh::setupMesh()
{
    vao = std::make_unique<llgl::VertexArray>();
    vbo = std::make_shared<llgl::VertexBuffer>();
    ebo = std::make_shared<llgl::ElementBuffer>();

    vbo->allocate(&vertices[0], vertices.size() * sizeof(Vertex));
    ebo->allocate(&indices[0], indices.size() * sizeof(unsigned int));

    // vertex positions
    vao->setAttrib<float>(0, 3, sizeof(Vertex), 0, *vbo);
    // vertex normals
    vao->setAttrib<float>(1, 3, sizeof(Vertex), offsetof(Vertex, Normal), *vbo);
}

void Mesh::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    program->getUniform("color").setVec3(0.5f, 0.8f, 0.4f);
    vao->bind();
    ebo->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

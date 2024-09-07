#include "Mesh.hpp"

#include <iostream>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"

#include "dataTemplates/VertexData.hpp"


void Border::setFirstPoint(glm::vec3 point)
{
    minX = point.x;
    maxX = point.x;
    minY = point.y;
    maxY = point.y;
    minZ = point.z;
    maxZ = point.z;
}

void Border::addPoint(glm::vec3 point)
{
    if(point.x < minX) minX = point.x;
    if(point.x > maxX) maxX = point.x;
    if(point.y < minY) minY = point.y;
    if(point.y > maxY) maxY = point.y;
    if(point.z < minZ) minZ = point.z;
    if(point.z > maxZ) maxZ = point.z;
}


Mesh::Mesh(
std::vector<Vertex> vertices, std::vector<unsigned int> indices, Border border)
: border{border}
{
    this->vertices = vertices;
    this->indices  = indices;

    initMesh();
    initBorder();
}

Mesh::Mesh(Mesh&& rhs)
{
    this->vertices = std::move(rhs.vertices);
    this->indices  = std::move(rhs.indices);

    this->vao = std::move(rhs.vao);
    this->vbo = std::move(rhs.vbo);
    this->ebo = std::move(rhs.ebo);

    this->vaoBorder      = std::move(rhs.vaoBorder);
    this->vboBorder      = std::move(rhs.vboBorder);
    this->eboBorder      = std::move(rhs.eboBorder);
    this->bolderElements = rhs.bolderElements;
}

Mesh::~Mesh() = default;

Border Mesh::getBorder()
{
    return border;
}

void Mesh::initMesh()
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

void Mesh::initBorder()
{
    std::cout << "init Border" << std::endl;
    vaoBorder = std::make_unique<llgl::VertexArray>();
    vboBorder = std::make_shared<llgl::VertexBuffer>();
    eboBorder = std::make_shared<llgl::ElementBuffer>();

    VertexData verticesBorder[]{
    {border.minX, border.minY, border.minZ},
    {border.maxX, border.minY, border.minZ},
    {border.maxX, border.maxY, border.minZ},
    {border.minX, border.maxY, border.minZ},
    {border.minX, border.minY, border.maxZ},
    {border.maxX, border.minY, border.maxZ},
    {border.maxX, border.maxY, border.maxZ},
    {border.minX, border.maxY, border.maxZ},
    };

    vboBorder->allocate(&verticesBorder, sizeof(verticesBorder));

    unsigned int indicesBorder[]{//front
    0, 1, 1, 2, 2, 3, 3, 0,
    //back
    0 + 4, 1 + 4, 1 + 4, 2 + 4, 2 + 4, 3 + 4, 3 + 4, 0 + 4,
    // //sides
    0, 0 + 4, 1, 1 + 4, 2, 2 + 4, 3, 3 + 4};
    bolderElements = sizeof(indicesBorder) / sizeof(unsigned int);

    eboBorder->allocate(&indicesBorder[0], sizeof(indicesBorder));

    // vertex positions
    vaoBorder->setAttrib<float>(0, 3, sizeof(float) * 3, 0, *vboBorder);
}

void Mesh::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    program->getUniform("color").setVec3(0.5f, 0.8f, 0.4f);
    vao->bind();
    ebo->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::drawBorder(std::shared_ptr<llgl::ShaderProgram> program)
{
    program->getUniform("color").setVec3(0.3f, 0.5f, 0.4f);
    vaoBorder->bind();
    eboBorder->bind();
    glDrawElements(GL_LINES, bolderElements, GL_UNSIGNED_INT, 0);
}

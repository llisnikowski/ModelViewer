#include "Mesh.hpp"

#include <algorithm>
#include <iostream>

#include "llgl/VertexArray.hpp"
#include "llgl/VertexBuffer.hpp"
#include "llgl/ElementBuffer.hpp"
#include "llgl/ShaderProgram.hpp"
#include "llgl/Uniform.hpp"

#include "dataTemplates/VertexData.hpp"

#include "camera/Camera.hpp"


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

//----------------------------------------------------------

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
std::vector<glm::vec3> verticesOpt, std::vector<unsigned int> indicesOpt,
Border border)
: vertices{vertices}
, indices{indices}
, optimalizeVertices{verticesOpt}
, optimalizeIndices{indicesOpt}
, border{border}
{
    initMesh();
    initBorder();
}

Mesh::Mesh(Mesh &&rhs)
: vao{std::move(rhs.vao)}
, vbo{std::move(rhs.vbo)}
, ebo{std::move(rhs.ebo)}
, vaoBorder{std::move(rhs.vaoBorder)}
, vboBorder{std::move(rhs.vboBorder)}
, eboBorder{std::move(rhs.eboBorder)}
, bolderElements{rhs.bolderElements}
, vertices{std::move(rhs.vertices)}
, indices{std::move(rhs.indices)}
, optimalizeVertices{std::move(rhs.optimalizeVertices)}
, optimalizeIndices{std::move(rhs.optimalizeIndices)}
, border{rhs.border}
{}

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

glm::vec3 Mesh::toVec3(glm::vec4 vec)
{
    return vec / vec.w;
}

void Mesh::reycast(Camera *camera, float x, float y)
{
    glm::mat4 mvp = camera->getProjection() * camera->getView()
                    * glm::scale(glm::mat4{1}, glm::vec3{0.05f, 0.05f, 0.05f});

    std::vector<glm::vec3> transforVertices;
    transforVertices.reserve(optimalizeVertices.size());
    for(unsigned int i = 0; i < optimalizeIndices.size(); i++) {
        transforVertices.push_back(
        toVec3(mvp * glm::vec4(optimalizeVertices[i], 1)));
    }

    checkVertex(transforVertices, {x, y});
}

void Mesh::checkVertex(std::vector<glm::vec3> &vertices, Position mouse)
{
    for(std::size_t i = 0; i < vertices.size(); i++) {
        float distance = glm::length(glm::vec2(vertices[i]) - mouse);

        if(distance < 0.02f) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

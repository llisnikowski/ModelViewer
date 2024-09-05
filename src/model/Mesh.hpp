#pragma once

#include "glm/glm.hpp"
#include <string>
#include <vector>
#include <memory>


namespace llgl
{
class VertexArray;
class VertexBuffer;
class ElementBuffer;
class ShaderProgram;
}

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(Mesh&& rhs);
    ~Mesh();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);
private:
    void setupMesh();

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

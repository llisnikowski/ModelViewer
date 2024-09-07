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

struct Border
{
    float minX{}, maxX{};
    float minY{}, maxY{};
    float minZ{}, maxZ{};

    void setFirstPoint(glm::vec3 point);
    void addPoint(glm::vec3 point);
};

class Loader;

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
    Border border);
    Mesh(Mesh&& rhs);
    ~Mesh();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);
    void drawBorder(std::shared_ptr<llgl::ShaderProgram> program);

    Border getBorder();
private:
    void initMesh();
    void initBorder();

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;

    std::unique_ptr<llgl::VertexArray> vaoBorder;
    std::shared_ptr<llgl::VertexBuffer> vboBorder;
    std::shared_ptr<llgl::ElementBuffer> eboBorder;
    int bolderElements{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Border border;
};

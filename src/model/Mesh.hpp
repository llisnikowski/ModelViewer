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
class Camera;

class Mesh
{
public:
    using Vertices = std::vector<glm::vec3>;
    using Position = glm::vec2;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
    std::vector<glm::vec3> verticesOpt, std::vector<unsigned int> indicesOpt,
    Border border);
    Mesh(Mesh &&rhs);
    ~Mesh();

    void draw(std::shared_ptr<llgl::ShaderProgram> program);
    void drawBorder(std::shared_ptr<llgl::ShaderProgram> program);

    Border getBorder();

    void reycast(Camera *camera, float x, float y);
private:
    void initMesh();
    void initBorder();

    void checkVertex(std::vector<glm::vec3> &vertices, Position mouse);

    glm::vec3 toVec3(glm::vec4 vec);

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;

    std::unique_ptr<llgl::VertexArray> vaoBorder;
    std::shared_ptr<llgl::VertexBuffer> vboBorder;
    std::shared_ptr<llgl::ElementBuffer> eboBorder;
    int bolderElements{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<glm::vec3> optimalizeVertices;
    std::vector<unsigned int> optimalizeIndices;

    Border border;
};

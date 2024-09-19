#pragma once
#include "glm/glm.hpp"
#include <memory>
#include <string>
#include <vector>

#include "Mesh.hpp"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace llgl
{
class VertexArray;
class VertexBuffer;
class ElementBuffer;
class ShaderProgram;
}
class Camera;

class Model
{
public:
    Model(const char *path);
    ~Model();
    void draw(std::shared_ptr<llgl::ShaderProgram> program);
    void drawBorder(std::shared_ptr<llgl::ShaderProgram> program);

    void reycast(Camera *camera, float x, float y);
private:
    std::vector<Mesh> meshes;
};

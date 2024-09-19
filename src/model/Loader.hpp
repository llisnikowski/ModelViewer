#pragma once
#include <string>
#include <vector>
#include <utility>

#include "glm/glm.hpp"

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Loader
{
public:
    using Index       = unsigned int;
    using Indices     = std::vector<Index>;
    using Vertices    = std::vector<Vertex>;
    using Position    = glm::vec3;
    using VerticesOpt = std::vector<Position>;

    Loader(std::string path);
    ~Loader();

    std::vector<Mesh> &getMesh();

private:
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::pair<VerticesOpt, Indices> getOptimalize(
    Vertices vertices, Indices indices);

    glm::vec3 toGlmVec3(aiVector3D vec);

    std::vector<Mesh> meshes;
};

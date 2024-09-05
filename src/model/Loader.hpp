#pragma once
#include <string>
#include <vector>

#include "glm/glm.hpp"

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Loader
{
public:
    Loader(std::string path);
    ~Loader();

    std::vector<Mesh> &getMesh();

private:
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    glm::vec3 toGlmVec3(aiVector3D vec);

    std::vector<Mesh> meshes;
};

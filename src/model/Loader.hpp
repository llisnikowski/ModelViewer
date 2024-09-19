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
    using Index    = unsigned int;
    using Indices  = std::vector<Index>;
    using Vertices = std::vector<Vertex>;
    using Position = glm::vec3;

    class Postprocess
    {
    public:
        virtual ~Postprocess()                                     = default;
        virtual Mesh convert(Vertices &vertices, Indices &indices) = 0;
    };

    Loader(std::string path, std::unique_ptr<Postprocess> &&postprocess);
    ~Loader();

    std::vector<Mesh> &getMesh();

private:
    void processNode(aiNode *node, const aiScene *scene);
    std::pair<Vertices, Indices> processMesh(aiMesh *mesh);

    glm::vec3 toGlmVec3(aiVector3D vec);

    std::unique_ptr<Postprocess> postprocess;
    std::vector<Mesh> meshes;
};

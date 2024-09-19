#include "Loader.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <stb_image.h>


Loader::Loader(std::string path, std::unique_ptr<Postprocess> &&postprocess)
: postprocess{std::move(postprocess)}
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(
    path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw std::invalid_argument(
        std::string("Error load model: ") + import.GetErrorString());
    }

    processNode(scene->mRootNode, scene);
}

Loader::~Loader() = default;

std::vector<Mesh> &Loader::getMesh()
{
    return meshes;
}

void Loader::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh             = scene->mMeshes[node->mMeshes[i]];
        auto [vertices, indices] = processMesh(mesh);
        if(postprocess) {
            meshes.push_back(postprocess->convert(vertices, indices));
        }
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

auto Loader::processMesh(aiMesh *mesh) -> std::pair<Vertices, Indices>
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.Position = toGlmVec3(mesh->mVertices[i]);

        // normals
        if(mesh->HasNormals()) {
            vertex.Normal = toGlmVec3(mesh->mNormals[i]);
        }

        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    // todo

    return {vertices, indices};
}

glm::vec3 Loader::toGlmVec3(aiVector3D vec)
{
    glm::vec3 vector;
    vector.x = vec.x;
    vector.y = vec.y;
    vector.z = vec.z;
    return vector;
}

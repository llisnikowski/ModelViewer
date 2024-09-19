#include "Model.hpp"

#include "Loader.hpp"
#include "LoaderPostprocess.hpp"

Model::Model(const char *path)
{
    Loader loader(path, std::make_unique<LoaderPostprocess>());
    meshes = std::move(loader.getMesh());
}

Model::~Model() = default;

void Model::draw(std::shared_ptr<llgl::ShaderProgram> program)
{
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(program);
    }
}

void Model::drawBorder(std::shared_ptr<llgl::ShaderProgram> program)
{
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].drawBorder(program);
    }
}

void Model::reycast(Camera *camera, float x, float y)
{
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].reycast(camera, x, y);
    }
}

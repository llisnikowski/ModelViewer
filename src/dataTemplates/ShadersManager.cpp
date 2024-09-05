#include "ShadersManager.hpp"

#include <iostream>

#include "llgl/Shader.hpp"
#include "llgl/ShaderProgram.hpp"
#include "dataTemplates/ShadersTemplate.hpp"

ShaderManager::ShaderManager()
{
    try {
        simpleVso
        = std::make_unique<llgl::Shader>(simpleVS, llgl::Shader::Type::VERTEX);
        simpleColorVso = std::make_unique<llgl::Shader>(
        posAndColorVs, llgl::Shader::Type::VERTEX);
        pickingVso
        = std::make_unique<llgl::Shader>(pickingVs, llgl::Shader::Type::VERTEX);
        meshVso
        = std::make_unique<llgl::Shader>(meshVs, llgl::Shader::Type::VERTEX);

        simpleFso = std::make_unique<llgl::Shader>(
        simpleFS, llgl::Shader::Type::FRAGMENT);
        simpleColorFso
        = std::make_unique<llgl::Shader>(colorFs, llgl::Shader::Type::FRAGMENT);
        pickingFso = std::make_unique<llgl::Shader>(
        pickingFs, llgl::Shader::Type::FRAGMENT);
    }
    catch(std::invalid_argument &ex) {
        std::cout << ex.what() << std::endl;
        return;
    }

    simple = std::make_shared<llgl::ShaderProgram>();
    simple->addShader(*simpleVso);
    simple->addShader(*simpleFso);
    simple->link();

    simpleColor = std::make_shared<llgl::ShaderProgram>();
    simpleColor->addShader(*simpleColorVso);
    simpleColor->addShader(*simpleColorFso);
    simpleColor->link();

    picking = std::make_shared<llgl::ShaderProgram>();
    picking->addShader(*pickingVso);
    picking->addShader(*pickingFso);
    picking->link();

    mesh = std::make_shared<llgl::ShaderProgram>();
    mesh->addShader(*meshVso);
    mesh->addShader(*simpleFso);
    mesh->link();
}

ShaderManager::~ShaderManager() = default;

std::shared_ptr<llgl::ShaderProgram> ShaderManager::getSimple()
{
    return simple;
}
void ShaderManager::useSimple()
{
    simple->bind();
}

std::shared_ptr<llgl::ShaderProgram> ShaderManager::getSimpleColor()
{
    return simpleColor;
}
void ShaderManager::useSimpleColor()
{
    simpleColor->bind();
}

void ShaderManager::usePicking()
{
    picking->bind();
}
std::shared_ptr<llgl::ShaderProgram> ShaderManager::getPicking()
{
    return picking;
}

void ShaderManager::useMesh()
{
    mesh->bind();
}
std::shared_ptr<llgl::ShaderProgram> ShaderManager::getMesh()
{
    return mesh;
}

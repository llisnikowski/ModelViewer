#include "llgl/Shader.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <stdexcept>

namespace llgl
{


Shader::Shader(const std::string &shader, Type type)
{
    compile(shader, type);
}

Shader::Shader(std::string filename, Type type, LoadFromFile)
{
    std::string shader = loadFile(filename);
    if(shader.empty())
        throw std::invalid_argument{"File: " + filename + " is empty"};

    compile(shader, type);
}

Shader::~Shader()
{
    if(this->shaderId) {
        glDeleteShader(this->shaderId);
    }
}

void Shader::compile(const std::string &shader, Type type)
{
    unsigned int typeNr = getTypeNumber(type);

    this->shaderId    = glCreateShader(typeNr);
    const char *c_str = shader.c_str();
    glShaderSource(this->shaderId, 1, &c_str, NULL);
    glCompileShader(this->shaderId);

    int success;
    glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(this->shaderId, 512, NULL, infoLog);
        throw std::invalid_argument{infoLog};
    }
}

unsigned int Shader::getTypeNumber(Type type)
{
    switch(type) {
    case Type::VERTEX: return GL_VERTEX_SHADER;
    case Type::FRAGMENT: return GL_FRAGMENT_SHADER;
    }
}

uint32_t Shader::getShaderId() const
{
    return this->shaderId;
}

std::string Shader::loadFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::in);
    if(file.is_open() == false)
        throw std::invalid_argument{"Cannot open file: " + filename};
    const size_t fileLength = file.tellg();
    file.seekg(0);

    std::string shader;
    shader.resize(fileLength);

    file.read(&shader.front(), fileLength);

    return shader;
}


} // llgl

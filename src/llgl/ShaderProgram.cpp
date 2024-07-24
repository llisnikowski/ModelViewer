#include "llgl/ShaderProgram.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/Shader.hpp"
#include <stdexcept>
#include "llgl/Uniform.hpp"

namespace llgl
{


ShaderProgram::ShaderProgram()
{
    this->shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    if(this->shaderProgram) {
        glDeleteProgram(this->shaderProgram);
    }
}

void ShaderProgram::addShader(const Shader &shader)
{
    glAttachShader(this->shaderProgram, shader.getShaderId());
}

void ShaderProgram::link()
{
    glLinkProgram(this->shaderProgram);

    int success;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        throw std::invalid_argument{infoLog};
    }
}

void ShaderProgram::bind()
{
    glUseProgram(this->shaderProgram);
}

Uniform ShaderProgram::getUniform(std::string &&name)
{
    return Uniform{glGetUniformLocation(this->shaderProgram, name.c_str())};
}

} // llgl

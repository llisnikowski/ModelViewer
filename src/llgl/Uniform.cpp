#include "llgl/Uniform.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{

Uniform::Uniform(int id)
: id{id}
{}

void Uniform::setBool(bool value) const
{
    glUniform1i(this->id, (int) value);
}

void Uniform::setInt(int value) const
{
    glUniform1i(this->id, value);
}

void Uniform::setUInt(unsigned int value) const
{
    glUniform1ui(this->id, value);
}

void Uniform::setFloat(float value) const
{
    glUniform1f(this->id, value);
}

void Uniform::setVec2(const glm::vec2 &value) const
{
    glUniform2fv(this->id, 1, &value[0]);
}

void Uniform::setVec2(float x, float y) const
{
    glUniform2f(this->id, x, y);
}

void Uniform::setVec3(const glm::vec3 &value) const
{
    glUniform3fv(this->id, 1, &value[0]);
}

void Uniform::setVec3(float x, float y, float z) const
{
    glUniform3f(this->id, x, y, z);
}

void Uniform::setVec4(const glm::vec4 &value) const
{
    glUniform4fv(this->id, 1, &value[0]);
}

void Uniform::setVec4(float x, float y, float z, float w) const
{
    glUniform4f(this->id, x, y, z, w);
}

void Uniform::setMat2(const glm::mat2 &mat) const
{
    glUniformMatrix2fv(this->id, 1, GL_FALSE, &mat[0][0]);
}

void Uniform::setMat3(const glm::mat3 &mat) const
{
    glUniformMatrix3fv(this->id, 1, GL_FALSE, &mat[0][0]);
}

void Uniform::setMat4(const glm::mat4 &mat) const
{
    glUniformMatrix4fv(this->id, 1, GL_FALSE, &mat[0][0]);
}


} // namespace llgl

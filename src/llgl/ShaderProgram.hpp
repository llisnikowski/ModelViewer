#pragma once
#include <string>

namespace llgl
{
class Shader;

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void addShader(const Shader& shader);
    void link();
    void bind();

private:
    unsigned int shaderProgram{};
};


} // namespace llgl

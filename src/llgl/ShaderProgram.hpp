#pragma once
#include <string>

namespace llgl
{
class Shader;
class Uniform;

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void addShader(const Shader &shader);
    void link();
    void bind();

    Uniform getUniform(std::string &&name);
private:
    unsigned int shaderProgram{};
};


} // namespace llgl

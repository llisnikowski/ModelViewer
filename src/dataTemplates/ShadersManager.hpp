#pragma once
#include <memory>


namespace llgl
{
class Shader;
class ShaderProgram;
}

/*
Shaders:
-simple:
    -data:
        -vec3 pos
    -uniforms:
        -mat4 mvp
        -vec3 col
*/

/*
Shaders:
-simpleColor:
    -data:
        -vec3 pos
        -vec3 col
    -uniforms:
        -mat4 mvp
*/

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void useSimple();
    std::shared_ptr<llgl::ShaderProgram> getSimple();
    void useSimpleColor();
    std::shared_ptr<llgl::ShaderProgram> getSimpleColor();

private:
    std::unique_ptr<llgl::Shader> simpleVso;
    std::unique_ptr<llgl::Shader> simpleColorVso;

    std::unique_ptr<llgl::Shader> simpleFso;
    std::unique_ptr<llgl::Shader> simpleColorFso;

    std::shared_ptr<llgl::ShaderProgram> simple;
    std::shared_ptr<llgl::ShaderProgram> simpleColor;
};

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

/*
Shaders:
-picking:
    -data:
        -vec3 pos
    -uniforms:
        -mat4 mvp
        -vec3 gObjectIndex
        -vec3 gDrawIndex
*/

/*
Shaders:
-mesh:
    -data:
        -vec3 pos
        -vec3 normal
    -uniforms:
        -mat4 model
        -vec3 view
        -vec3 projection
        -vec3 color
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
    void usePicking();
    std::shared_ptr<llgl::ShaderProgram> getPicking();
    void useMesh();
    std::shared_ptr<llgl::ShaderProgram> getMesh();

private:
    std::unique_ptr<llgl::Shader> simpleVso;
    std::unique_ptr<llgl::Shader> simpleColorVso;
    std::unique_ptr<llgl::Shader> pickingVso;
    std::unique_ptr<llgl::Shader> meshVso;

    std::unique_ptr<llgl::Shader> simpleFso;
    std::unique_ptr<llgl::Shader> simpleColorFso;
    std::unique_ptr<llgl::Shader> pickingFso;

    std::shared_ptr<llgl::ShaderProgram> simple;
    std::shared_ptr<llgl::ShaderProgram> simpleColor;
    std::shared_ptr<llgl::ShaderProgram> picking;
    std::shared_ptr<llgl::ShaderProgram> mesh;
};

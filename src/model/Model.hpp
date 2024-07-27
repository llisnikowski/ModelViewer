#pragma once
#include <array>
#include <memory>

class Camera;

namespace llgl
{
class VertexArray;
class VertexBuffer;
class ElementBuffer;
class Shader;
class ShaderProgram;
}

class Model
{
public:
    explicit Model(Camera &camera);
    ~Model();

    void draw();

private:
    void loadShader();
    void init();

    int triangleCount{};

    Camera &camera;

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::shared_ptr<llgl::ElementBuffer> ebo;
    std::unique_ptr<llgl::ShaderProgram> program;
    std::shared_ptr<llgl::Shader> vertexShader;
    std::shared_ptr<llgl::Shader> fragmentShader;
};

#pragma once
#include <array>
#include <memory>

class Camera;

namespace llgl
{
class VertexArray;
class VertexBuffer;
class Shader;
class ShaderProgram;
}

class MainAxis
{
public:
    explicit MainAxis(Camera &camera);
    ~MainAxis();

    void draw();

private:
    void loadShader();
    void init();

    void initData();
    void initProgram();

    int lineCount{};

    Camera &camera;

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
    std::unique_ptr<llgl::ShaderProgram> program;
    std::shared_ptr<llgl::Shader> vertexShader;
    std::shared_ptr<llgl::Shader> fragmentShader;
};

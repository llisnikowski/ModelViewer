#pragma once
#include <array>
#include <memory>
#include <mutex>
#include <optional>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"


namespace llgl
{
class VertexArray;
class VertexBuffer;
class ShaderProgram;
}

class HelpLine
{
public:
    explicit HelpLine();
    ~HelpLine();

    void draw();

    void setP1(glm::vec3 vec);
    void setP2(glm::vec3 vec);

private:
    void init();

    void initData();

    int lineCount{};

    std::mutex mutex;

    bool changeLine{};
    glm::vec3 p1{0, 0, 0};
    glm::vec3 p2{1, 0, 0};

    std::unique_ptr<llgl::VertexArray> vao;
    std::shared_ptr<llgl::VertexBuffer> vbo;
};

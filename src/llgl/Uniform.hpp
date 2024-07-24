#pragma once
#include "glm/glm.hpp"

namespace llgl
{
class ShaderProgram;

class Uniform
{
private:
    explicit Uniform(int id);

    friend class ShaderProgram;
public:
    void setBool(bool value) const;
    void setInt(int value) const;
    void setFloat(float value) const;
    void setVec2(const glm::vec2 &value) const;
    void setVec2(float x, float y) const;
    void setVec3(const glm::vec3 &value) const;
    void setVec3(float x, float y, float z) const;
    void setVec4(const glm::vec4 &value) const;
    void setVec4(float x, float y, float z, float w) const;
    void setMat2(const glm::mat2 &mat) const;
    void setMat3(const glm::mat3 &mat) const;
    void setMat4(const glm::mat4 &mat) const;

private:
    int id;
};

} // namespace llgl

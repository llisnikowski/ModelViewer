#pragma once
#include <string>
#include <memory>

namespace llgl
{

class Shader
{
public:
    enum class Type
    {
        VERTEX,
        FRAGMENT
    };

    class LoadFromFile
    {
    };

    Shader(const std::string &shader, Type type);
    Shader(std::string &&filename, Type type, LoadFromFile);
    Shader(const std::string &filename, Type type, LoadFromFile);
    ~Shader();

    unsigned int getShaderId() const;

private:
    void compile(const std::string &shader, Type type);
    std::string loadFile(const std::string &filename);

    static unsigned int getTypeNumber(Type type);

    unsigned int shaderId{};
};


} // namespace llgl

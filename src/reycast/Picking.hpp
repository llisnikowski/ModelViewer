#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

namespace llgl
{
struct Size;
class ShaderProgram;
}

struct PickingObject
{
public:
    virtual ~PickingObject() = default;

    virtual void drawPicking() = 0;

    virtual void mouseEntered(unsigned int primID) {};
    virtual void mouseExited() {};
};

class Picking
{
public:
    struct PixelInfo
    {
        unsigned int objectID = 0;
        unsigned int drawID   = 0;
        unsigned int primID   = 0;
    };

    Picking(llgl::Size size);
    ~Picking();

    void setWindowSize(llgl::Size size);


    void startCheck(std::shared_ptr<llgl::ShaderProgram> program);
    void drawObject(int nr, PickingObject *object, glm::mat4 mvp);
    PixelInfo endCheck(unsigned int x, unsigned int y);


    void enableWriting();
    void disableWriting();


    PixelInfo getPixel(unsigned int x, unsigned int y);

private:


    GLuint frameBuffor    = 0;
    GLuint pickingTexture = 0;
    GLuint depthTexture   = 0;

    std::vector<PickingObject *> objects;
    std::shared_ptr<llgl::ShaderProgram> shaderProgram;
};

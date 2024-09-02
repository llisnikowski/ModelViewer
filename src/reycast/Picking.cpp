#include "Picking.hpp"
#include "llgl/Size.hpp"
#include "llgl/Uniform.hpp"
#include "llgl/ShaderProgram.hpp"
#include <iostream>

Picking::Picking(llgl::Size size)
{
    // Create the FBO
    glGenFramebuffers(1, &frameBuffor);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffor);

    // Create the texture object for the primitive information buffer
    glGenTextures(1, &pickingTexture);
    glBindTexture(GL_TEXTURE_2D, pickingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, size.width, size.height, 0,
    GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(
    GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);

    // Create the texture object for the depth buffer
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.width, size.height,
    0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(
    GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    // Verify that the FBO is correct
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        exit(1);
    }

    // Restore the default framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Picking::~Picking()
{
    if(frameBuffor) {
        glDeleteFramebuffers(1, &frameBuffor);
    }
    if(pickingTexture) {
        glDeleteTextures(1, &pickingTexture);
    }
    if(depthTexture) {
        glDeleteTextures(1, &depthTexture);
    }
}

void Picking::setWindowSize(llgl::Size size)
{
    glBindTexture(GL_TEXTURE_2D, pickingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, size.width, size.height, 0,
    GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.width, size.height,
    0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Picking::enableWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffor);
}

void Picking::disableWriting()
{
    // Bind back the default framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Picking::startCheck(std::shared_ptr<llgl::ShaderProgram> program)
{
    shaderProgram = program;
    shaderProgram->bind();
    enableWriting();
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Picking::drawObject(int nr, PickingObject *object, glm::mat4 mvp)
{
    shaderProgram->getUniform("mvp").setMat4(mvp);
    shaderProgram->getUniform("gObjectIndex").setUInt(nr);
    shaderProgram->getUniform("gDrawIndex").setUInt(1);
    object->drawPicking();
}

Picking::PixelInfo Picking::endCheck(unsigned int x, unsigned int y)
{
    disableWriting();
    PixelInfo pixel = getPixel(x, y);
    return pixel;
}

Picking::PixelInfo Picking::getPixel(unsigned int x, unsigned int y)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffor);
    glReadBuffer(GL_COLOR_ATTACHMENT0);

    PixelInfo Pixel;
    glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &Pixel);

    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    return Pixel;
}

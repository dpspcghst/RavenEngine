// FBManager.h
#pragma once

#include <glad/glad.h>

namespace RavenEngine {

class FBManager {
public:
    FBManager(int width, int height);
    ~FBManager();

    bool Initialize();
    GLuint GetCurrentTexture();

private:
    bool CreateFramebuffer();
    bool CreateTextureForFramebuffer();
    bool CheckFramebufferStatus();

    int gameWidth, gameHeight;
    GLuint framebufferObject;
    GLuint currentTexture;
};

} // namespace RavenEngine
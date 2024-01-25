// FBManager.cpp
#include "FBManager.h"
#include <iostream>

namespace RavenEngine {

FBManager::FBManager(int width, int height)
    : gameWidth(width), gameHeight(height), framebufferObject(0), currentTexture(0) {
    std::cout << "FBManager Constructor Ping" << std::endl;
    std::cout << "FBManager created with size: " << gameWidth << "x" << gameHeight << std::endl;
}

FBManager::~FBManager() {
    std::cout << "FBManager destructor called" << std::endl;
    glDeleteFramebuffers(1, &framebufferObject);
    glDeleteTextures(1, &currentTexture);
}

bool FBManager::Initialize() {
    if (!CreateFramebuffer() || !CreateTextureForFramebuffer()) {
        return false;
    }

    return CheckFramebufferStatus();
}

GLuint FBManager::GetCurrentTexture() {
    return currentTexture;
}

bool FBManager::CreateFramebuffer() {
    glGenFramebuffers(1, &framebufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);
    return framebufferObject != 0;
}

bool FBManager::CreateTextureForFramebuffer() {
    glGenTextures(1, &currentTexture);
    glBindTexture(GL_TEXTURE_2D, currentTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gameWidth, gameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, currentTexture, 0);
    return currentTexture != 0;
}

bool FBManager::CheckFramebufferStatus() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete" << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

} // namespace RavenEngine
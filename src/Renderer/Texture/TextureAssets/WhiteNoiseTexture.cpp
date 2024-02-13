#include "WhiteNoiseTexture.h"
#include <cstdlib> // For rand()

namespace RavenEngine {

WhiteNoiseTexture::WhiteNoiseTexture(int width, int height) : width(width), height(height), textureID(0) {
    Generate();
}

WhiteNoiseTexture::~WhiteNoiseTexture() {
    glDeleteTextures(1, &textureID);
}

void WhiteNoiseTexture::Generate() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    unsigned char* noiseData = new unsigned char[width * height];
    generateNoiseData(noiseData);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, noiseData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    delete[] noiseData;
}

void WhiteNoiseTexture::Update() {
    unsigned char* noiseData = new unsigned char[width * height];
    generateNoiseData(noiseData);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, noiseData);

    delete[] noiseData;
}

GLuint WhiteNoiseTexture::GetTextureID() const {
    return textureID;
}

void WhiteNoiseTexture::generateNoiseData(unsigned char* data) {
    for (int i = 0; i < width * height; ++i) {
        data[i] = rand() % 256; // Random grayscale value
    }
}

} // namespace RavenEngine

#ifndef RAVENENGINE_WHITENOISETEXTURE_H
#define RAVENENGINE_WHITENOISETEXTURE_H

#include <glad/glad.h>

namespace RavenEngine {

class WhiteNoiseTexture {
public:
    WhiteNoiseTexture(int width, int height);
    ~WhiteNoiseTexture();

    void Generate();
    void Update(); // Call this per frame if dynamic noise is needed
    GLuint GetTextureID() const;

private:
    int width, height;
    GLuint textureID;
    void generateNoiseData(unsigned char* data);
};

} // namespace RavenEngine

#endif // RAVENENGINE_WHITENOISETEXTURE_H

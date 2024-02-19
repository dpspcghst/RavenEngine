#version 420 core

layout (location = 0) in vec3 aPos; // Position of the vertex
layout (location = 1) in vec2 aTexCoords; // Texture coordinates of the vertex

// Uniforms for model, view, and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Uniforms for texture transformations
uniform vec2 textureScale;
uniform vec2 textureTranslation;
uniform float textureRotation; // Rotation in radians

out vec2 TexCoords; // Output for the texture coordinates

// Function to rotate texture coordinates
vec2 rotateTextureCoords(vec2 coords, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    // Translate coords to origin for rotation then translate back
    coords -= 0.5;
    vec2 rotatedCoords = vec2(
        coords.x * c - coords.y * s,
        coords.x * s + coords.y * c
    );
    return rotatedCoords + 0.5;
}

void main() {
    // Transform the vertex position by the model, view, and projection matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Apply the texture transformations
    vec2 rotatedCoords = rotateTextureCoords(aTexCoords, textureRotation);
    TexCoords = rotatedCoords * textureScale + textureTranslation;
}

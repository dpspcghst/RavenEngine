#version 420 core

layout (location = 0) in vec3 aPos; // Position of the vertex
layout (location = 1) in vec2 aTexCoords; // Texture coordinates of the vertex

// Uniforms for model, view, and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords; // Output for the texture coordinates

void main() {
    // Transform the vertex position by the model, view, and projection matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Pass the texture coordinates to the fragment shader
    TexCoords = aTexCoords;
}
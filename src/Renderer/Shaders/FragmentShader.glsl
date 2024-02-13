#version 420 core

out vec4 FragColor;

// Uniform block for material properties
layout(std140) uniform MaterialProperties {
    vec4 color; // Color of the material
    // Add more material properties here as needed
} material;

uniform sampler2D u_Texture; // Uniform for the texture
uniform int u_HasTexture; // Uniform for indicating whether a texture is present or not

in vec2 TexCoords; // Input for the texture coordinates, this should be passed from the vertex shader

void main() {
    // Sample the texture
    vec4 texColor = texture(u_Texture, TexCoords);

    // Use the material color as the base color
    FragColor = material.color;

    // If a texture is present and its alpha is greater than 0, apply the texture color
    if (u_HasTexture == 1 && texColor.a > 0.0) {
        FragColor *= texColor;
    }
}
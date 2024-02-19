#version 420 core

out vec4 FragColor;

// Uniform block for material properties
layout(std140) uniform MaterialProperties {
    vec4 color; // Color of the material
} material;

uniform sampler2D u_Texture; // Uniform for the texture
uniform int u_HasTexture; // Uniform for indicating whether a texture is present or not
uniform float u_Alpha; // Uniform for controlling the alpha value

in vec2 TexCoords; // Input for the texture coordinates from the vertex shader

void main() {
    if (u_HasTexture == 1) {
        vec4 texColor = texture(u_Texture, TexCoords);
        texColor.a *= u_Alpha; // Apply the alpha control
        // Blend the texture color with the material color based on the texture's alpha value.
        // This ensures that the material color shows through where the texture is transparent.
        FragColor = mix(material.color, texColor, texColor.a);
    } else {
        // If no texture is present, use the material color.
        FragColor = material.color;
    }
}
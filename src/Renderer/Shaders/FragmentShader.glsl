#version 420 core

out vec4 FragColor;

// Uniform block for material properties
layout(std140) uniform MaterialProperties {
    vec4 color; // Color of the material
    // Add more material properties here as needed
} material;

void main() {
    // Set the fragment color to the material color
    FragColor = material.color;
}

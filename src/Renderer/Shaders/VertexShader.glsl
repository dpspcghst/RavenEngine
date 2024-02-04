#version 420 core

layout (location = 0) in vec3 aPos; // Position of the vertex

// Uniforms for model, view, and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Transform the vertex position by the model, view, and projection matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

// doodleShader.glsl
precision mediump float;

uniform vec2 u_resolution;
uniform float u_thickness;
uniform vec3 u_color;

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution.xy;

    // Example line equation for demo purposes
    float dist = abs(st.y - st.x); // You'll replace this with dynamic line drawing logic

    // Use the uniform thickness
    vec3 color = vec3(0.0);
    if (dist < u_thickness) {
        color = u_color; // Use the uniform color
    }

    gl_FragColor = vec4(color, 1.0);
}

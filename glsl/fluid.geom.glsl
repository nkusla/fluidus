#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 34) out;

uniform mat4 view;
uniform mat4 projection;

const float PI = 3.14159265359;
const float radius = 0.015;

void main() {
    vec4 center = gl_in[0].gl_Position;
    const int numSegments = 16; // Number of segments to approximate the circle

    // Emit the circle points
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0 * PI * float(i) / float(numSegments);
        vec4 offset = vec4(cos(angle) * radius, sin(angle) * radius, 0.0, 0.0);
        gl_Position = projection * view * (center + offset);
        EmitVertex();

        // Emit the center point again to create a strip
        gl_Position = projection * view * center;
        EmitVertex();
    }
    EndPrimitive();
}
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 acceleration;
layout(location = 3) in float mass;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec4 fragColor;

void main() {
    fragColor = vec4(153.0 / 255.0, 192.0 / 255.0, 227.0 / 255.0, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}
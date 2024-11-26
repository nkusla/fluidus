#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 acceleration;
layout(location = 3) in float mass;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out float property;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    property = length(velocity);
}
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 force;
layout(location = 3) in float mass;

uniform mat4 MVP;
out float property;

void main() {
	gl_Position = MVP * vec4(position, 1.0);
	gl_PointSize = 5.0;
	property = length(velocity);
}
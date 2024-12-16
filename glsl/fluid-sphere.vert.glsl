#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;

uniform mat4 MVP;
out float velocityMagnitude;

void main() {
	velocityMagnitude = length(velocity);
	gl_Position = vec4(position, 1.0);
}
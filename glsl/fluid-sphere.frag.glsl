#version 330 core

in float velocityMagnitude;
out vec4 fragColor;

void main() {
	vec3 color = vec3(26.0, 202.0, 226.0) / 255.0;

	fragColor = vec4(color, 1.0);
}
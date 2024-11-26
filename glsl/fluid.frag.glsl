#version 330 core

in float property;
out vec4 fragColor;

void main() {
	vec3 color_slow = vec3(26.0, 202.0, 226.0) / 255.0; // blue
	vec3 color_fast = vec3(255.0, 33.0, 33.0) / 255.0; // red

	float t = clamp(property, 0.0, 1.0);
	vec3 color = mix(color_slow, color_fast, t);

	fragColor = vec4(color, 1.0);
}
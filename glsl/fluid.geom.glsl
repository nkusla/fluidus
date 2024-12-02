// ATM this is just a passthrough geometry shader that takes a single point and renders it as a point.
// THIS IS NOT USED IN THE CURRENT IMPLEMENTATION

#version 330 core

layout(points) in;
layout(points, max_vertices = 32) out;

uniform mat4 view;
uniform mat4 projection;

void main() {
	vec4 center = gl_in[0].gl_Position;
	gl_PointSize = 5.0;
	gl_Position = projection * view * center;
	EmitVertex();
	EndPrimitive();
}
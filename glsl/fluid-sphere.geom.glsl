#version 330 core
#define M_PI 3.1415926535897932384626433832795

layout(points) in;
layout(points, max_vertices = 32) out;

uniform mat4 MVP;

const float radius = 0.03;
const int sectorCount = 6;
const int stackCount = 4;
const float sectorStep = 2 * M_PI / sectorCount;
const float stackStep = M_PI / stackCount;

in float velocityMagnitude[];
out float geomVelocityMagnitude;

void main() {
	geomVelocityMagnitude = velocityMagnitude[0];

	vec4 center = gl_in[0].gl_Position;

	for (int i = 0; i <= stackCount; i++) {
		float stackAngle = M_PI / 2 - i * stackStep;
		float xy = radius * cos(stackAngle);
		float z = radius * sin(stackAngle);

		for (int j = 0; j <= sectorCount; j++) {
			float sectorAngle = j * sectorStep;

			float x = xy * cos(sectorAngle);
			float y = xy * sin(sectorAngle);

			vec4 pos = center + vec4(x, y, z, 0.0);
			gl_Position = MVP * pos;
			gl_PointSize = 2.0;
			EmitVertex();
		}
	}
	EndPrimitive();
}
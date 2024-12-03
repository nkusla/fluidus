#include "ExternalForces.hpp"

glm::vec3 ExternalForces::WaveSide(float x, float time) {
	float leftWall = -Config::CONTAINER_DIMENSIONS.x / 2.0f;
	float distance = abs(x - leftWall);
	float scale = 0.05f;

	float decay = exp(-scale * pow(x - leftWall, 2));
	float wave = 180.0f * sin(2 * M_PI * time) * decay;

	float xForce = -wave;
	float yForce = 0.0f;
	float zForce = 0.0f;

	return glm::vec3(xForce, yForce, zForce);
}
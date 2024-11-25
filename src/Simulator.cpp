#include "../include/Simulator.hpp"

Simulator::Simulator(
	std::shared_ptr<std::vector<Particle>> particles,
	std::shared_ptr<Container> container) {

	this->particles = particles;
	this->container = container;
}

void Simulator::Step() {

	for (auto &p : *particles) {
		p.acceleration += GRAVITY;
		p.velocity += p.acceleration * Config::STEP;
		p.position += p.velocity * Config::STEP;

		CheckWallCollision(p);
	}
}

void Simulator::CheckWallCollision(Particle &p) {
	glm::vec3 dimensions = container->GetDimensions();
	float lowerBoundY = -dimensions.y / 2.0f;
	float upperBoundY = dimensions.y / 2.0f;
	float lowerBoundX = -dimensions.x / 2.0f;
	float upperBoundX = dimensions.x / 2.0f;
	float lowerBoundZ = -dimensions.z / 2.0f;
	float upperBoundZ = dimensions.z / 2.0f;

	// Check collision with Y walls
	if (p.position.y <= lowerBoundY) {
		p.position.y = lowerBoundY;
		p.velocity.y = -p.velocity.y * Config::DAMPING;
		p.acceleration += GRAVITY;
	} else if (p.position.y >= upperBoundY) {
		p.position.y = upperBoundY;
		p.velocity.y = -p.velocity.y * Config::DAMPING;
		p.acceleration += GRAVITY;
	}

	// Check collision with X walls
	if (p.position.x <= lowerBoundX) {
		p.position.x = lowerBoundX;
		p.velocity.x = -p.velocity.x * Config::DAMPING;
		p.acceleration.x = 0.0f; // Reset other accelerations
	} else if (p.position.x >= upperBoundX) {
		p.position.x = upperBoundX;
		p.velocity.x = -p.velocity.x * Config::DAMPING;
		p.acceleration.x = 0.0f; // Reset other accelerations
	}

	// Check collision with Z walls
	if (p.position.z <= lowerBoundZ) {
		p.position.z = lowerBoundZ;
		p.velocity.z = -p.velocity.z * Config::DAMPING;
		p.acceleration.z = 0.0f; // Reset other accelerations
	} else if (p.position.z >= upperBoundZ) {
		p.position.z = upperBoundZ;
		p.velocity.z = -p.velocity.z * Config::DAMPING;
		p.acceleration.z = 0.0f; // Reset other accelerations
	}
}
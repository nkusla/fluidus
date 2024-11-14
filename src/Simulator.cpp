#include "../include/Simulator.hpp"

Simulator::Simulator(
	std::shared_ptr<std::vector<Particle>> particles,
	std::shared_ptr<Container> container) {

	this->particles = particles;
	this->container = container;
}

void Simulator::step() {
	glm::vec3 dimensions = container->getDimensions();
	float lowerBound = -dimensions.y / 2.0f;

	for (auto &p : *particles) {
		p.acceleration += GRAVITY;
		p.velocity += p.acceleration * Config::STEP;
		p.position += p.velocity * Config::STEP;

		if (p.position.y <= lowerBound) {
			p.position.y = lowerBound;
			p.velocity.y = -p.velocity.y * Config::DAMPING;
			continue;
		}
	}
}
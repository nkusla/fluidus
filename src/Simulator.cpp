#include "../include/Simulator.hpp"

Simulator::Simulator(std::shared_ptr<std::vector<Particle>> particles) {
	this->particles = particles;
}

void Simulator::step() {
	for (auto &p : *particles) {
		p.acceleration += GRAVITY;
		p.velocity += p.acceleration * Config::STEP;
		p.position += p.velocity * Config::STEP;

		if (p.position.y <= -0.5f) {
			p.position.y = -0.5f;
		}
	}
}
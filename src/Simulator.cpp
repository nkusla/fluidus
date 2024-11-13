#include "../include/Simulator.hpp"

void Simulator::step() {
	for (auto &p : *particles) {
		p.acceleration += GRAVITY;
		p.velocity += p.acceleration * Config::STEP;
		p.position += p.velocity * Config::STEP;
	}
}
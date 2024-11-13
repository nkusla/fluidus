#include "../include/Fluid.hpp"

Fluid::Fluid() {
	particles = std::make_shared<std::vector<Particle>>();
}
#ifndef FLUID_HPP
#define FLUID_HPP

#include "Particle.hpp"

#include <memory>
#include <vector>

class Fluid {
	private:

	public:
		std::shared_ptr<std::vector<Particle>> particles;

		Fluid();
};

#endif // FLUID_HPP
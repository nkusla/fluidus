#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include "Particle.hpp"
#include "Config.hpp"

class Simulator {
	private:
		std::shared_ptr<std::vector<Particle>> particles = nullptr;

	public:
		Simulator(std::shared_ptr<std::vector<Particle>> particles);

		void step();
};

#endif // ENGINE_HPP
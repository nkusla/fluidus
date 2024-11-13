#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include "Particle.hpp"
#include "Config.hpp"

class Simulator {
	private:

	public:
		std::shared_ptr<std::vector<Particle>> particles = nullptr;

		void step();
};

#endif // ENGINE_HPP
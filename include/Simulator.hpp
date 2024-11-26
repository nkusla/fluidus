#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>
#include <omp.h>

#include "Particle.hpp"
#include "Config.hpp"
#include "Container.hpp"

class Simulator {
	private:
		std::shared_ptr<std::vector<Particle>> particles = nullptr;
		std::shared_ptr<Container> container = nullptr;

		double time = 0.0;
		bool stopped = false;

	public:
		Simulator(std::shared_ptr<std::vector<Particle>> particles, std::shared_ptr<Container> container);
		double GetTime() const;

		void StartStop();
		void Reset();
		void Step();
		void CheckWallCollision(Particle &p);
};

#endif // ENGINE_HPP
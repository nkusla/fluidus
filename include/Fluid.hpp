#ifndef FLUID_HPP
#define FLUID_HPP

#include "Particle.hpp"
#include "IObject.hpp"
#include "ShaderLoader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include <random>

class Fluid : public IObject {
	private:
		void generateParticles(int count);
	public:
		std::shared_ptr<std::vector<Particle>> particles = nullptr;

		Fluid();
		void render(const glm::mat4 &view, const glm::mat4 &projection) override;
		void update();
};

#endif // FLUID_HPP
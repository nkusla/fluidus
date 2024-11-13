#ifndef FLUID_HPP
#define FLUID_HPP

#include "Particle.hpp"
#include "IObject.hpp"
#include "ShaderLoader.hpp"
#include "Config.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include <random>

class Fluid : public IObject {
	private:
		std::shared_ptr<std::vector<Particle>> particles = nullptr;

	public:
		Fluid();
		void generateRandParticles(int count);
		std::shared_ptr<std::vector<Particle>> getParticles();
		void render(const glm::mat4 &view, const glm::mat4 &projection) override;
		void updateVBO() override;
};

#endif // FLUID_HPP
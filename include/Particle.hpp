#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>

struct Particle {
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 force = glm::vec3(0.0f);
	float mass = 1.0f;
	float density = 0.0f;
};

#endif // PARTICLE_HPP
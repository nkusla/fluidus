#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>

struct Particle {
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	double mass;
};


#endif // PARTICLE_HPP
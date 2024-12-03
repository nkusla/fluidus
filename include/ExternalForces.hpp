#ifndef EXTERNAL_FORCES_HPP
#define EXTERNAL_FORCES_HPP

#include <glm/glm.hpp>
#include "Config.hpp"

class ExternalForces {
	public:
		static glm::vec3 WaveSide(float x, float time);
};

#endif // EXTERNAL_FORCES_HPP
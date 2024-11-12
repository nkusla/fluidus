#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glm/glm.hpp>

class Config {
	public:
		static glm::vec3 CONTAINER_DIMENSIONS;
		static glm::vec2 SCREEN_SIZE;
		static float ZOOM_FACTOR;
		static float ROTATION_ANGLE;
};

#endif
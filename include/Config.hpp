#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glm/glm.hpp>

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)
#define ORIGIN glm::vec3(0.0f, 0.0f, 0.0f)
#define GRAVITY glm::vec3(0.0f, -Config::G, 0.0f)

class Config {
	public:
		static glm::vec3 CONTAINER_DIMENSIONS;
		static glm::vec2 SCREEN_SIZE;
		static float ZOOM_FACTOR;
		static float ROTATION_ANGLE;
		static float G;
		static float STEP;
		static int PARTICLE_COUNT;
};

#endif
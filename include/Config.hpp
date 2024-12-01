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
		static unsigned int SEED;
		static glm::vec3 CONTAINER_DIMENSIONS;
		static int PARTICLE_COUNT;

		// Graphics parameters
		static glm::vec2 SCREEN_SIZE;
		static float ZOOM_FACTOR;
		static float ROTATION_ANGLE;

		// Physics parameters
		static float G;
		static float G_MIN;
		static float G_MAX;
		static float G_STEP;

		static float TIME_STEP;
		static float TIME_STEP_MIN;
		static float TIME_STEP_MAX;
		static float TIME_STEP_STEP;

		static float DAMPING;

		static float SMOOTHING_RADIUS;
		static float SMOOTHING_RADIUS_MIN;
		static float SMOOTHING_RADIUS_MAX;
		static float SMOOTHING_RADIUS_STEP;

		static float REST_DENSITY;
		static float REST_DENSITY_MIN;
		static float REST_DENSITY_MAX;
		static float REST_DENSITY_STEP;

		static float STIFFNESS_COEFF;
		static float STIFFNESS_COEFF_MIN;
		static float STIFFNESS_COEFF_MAX;
		static float STIFFNESS_COEFF_STEP;
};

#endif
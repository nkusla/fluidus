#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glm/glm.hpp>

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)
#define ORIGIN glm::vec3(0.0f, 0.0f, 0.0f)
#define GRAVITY glm::vec3(0.0f, -Config::G, 0.0f)
#define NO_POINT glm::vec3(INFINITY)

class Config {
	public:
		static float TARGET_FPS;
		static unsigned int SEED;
		static glm::vec3 CONTAINER_DIMENSIONS;
		static float CONTAINER_DIMENSIONS_MIN;
		static float CONTAINER_DIMENSIONS_MAX;
		static bool ENABLE_EXTERNAL_FORCES;

		static int PARTICLE_COUNT;
		static int PARTICLE_COUNT_MIN;
		static int PARTICLE_COUNT_MAX;
		static int PARTICLE_COUNT_STEP;

		static float RAYCAST_RADIUS;
		static float RAYCAST_FORCE;

		// Graphics parameters
		static glm::vec2 SCREEN_SIZE;
		static float ZOOM_FACTOR;
		static float ROTATION_ANGLE;
		static glm::vec3 DEFAULT_CAMERA_POS;

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
		static float DAMPING_MIN;
		static float DAMPING_MAX;
		static float DAMPING_STEP;

		static float SMOOTHING_RADIUS;
		static float SMOOTHING_RADIUS_MIN;
		static float SMOOTHING_RADIUS_MAX;
		static float SMOOTHING_RADIUS_STEP;

		static float REST_DENSITY;
		static float REST_DENSITY_MIN;
		static float REST_DENSITY_MAX;
		static float REST_DENSITY_STEP;

		static float STIFFNESS;
		static float STIFFNESS_MIN;
		static float STIFFNESS_MAX;
		static float STIFFNESS_STEP;

		static float VISCOSITY;
		static float VISCOSITY_MIN;
		static float VISCOSITY_MAX;
		static float VISCOSITY_STEP;

		static float SURFACE_TENSION;
		// static float SURFACE_TENSION_MIN;
		// static float SURFACE_TENSION_MAX;
		// static float SURFACE_TENSION_STEP;
		static float SURFACE_TENSION_THRESHOLD;
};

#endif
#include "../include/Config.hpp"

unsigned int Config::SEED = 1616;
glm::vec3 Config::CONTAINER_DIMENSIONS = glm::vec3(1.0f, 1.0f, 1.0f);
int Config::PARTICLE_COUNT = 500;

// Graphics parameters
glm::vec2 Config::SCREEN_SIZE = glm::vec2(1366, 768);
float Config::ZOOM_FACTOR = 0.5f;
float Config::ROTATION_ANGLE = 90.0f;

// Physics parameters
float Config::G = 0.01f;
float Config::G_MIN = 0.0f;
float Config::G_MAX = 20.0f;
float Config::G_STEP = 1e-3f;

float Config::TIME_STEP = 0.01f;
float Config::TIME_STEP_MIN = 1e-4f;
float Config::TIME_STEP_MAX = 0.5f;
float Config::TIME_STEP_STEP = 1e-4f;

float Config::DAMPING = 0.3f;

float Config::SMOOTHING_RADIUS = 0.4f;
float Config::SMOOTHING_RADIUS_MIN = 0.1f;
float Config::SMOOTHING_RADIUS_MAX = 3.0f;
float Config::SMOOTHING_RADIUS_STEP = 0.1f;

float Config::REST_DENSITY = 5.0f;
float Config::REST_DENSITY_MIN = 1.0f;
float Config::REST_DENSITY_MAX = 10.0f;
float Config::REST_DENSITY_STEP = 0.1f;

float Config::STIFFNESS_COEFF = 1.0f;
float Config::STIFFNESS_COEFF_MIN = 0.1f;
float Config::STIFFNESS_COEFF_MAX = 100.0f;
float Config::STIFFNESS_COEFF_STEP = 0.1f;

#include "../include/Config.hpp"

unsigned int Config::SEED = 1616;
glm::vec3 Config::CONTAINER_DIMENSIONS = glm::vec3(1.0f, 1.0f, 1.0f);
float Config::CONTAINER_DIMENSIONS_MIN = 1.0f;
float Config::CONTAINER_DIMENSIONS_MAX = 10.0f;
bool Config::ENABLE_EXTERNAL_FORCES = false;

int Config::PARTICLE_COUNT = 800;

float Config::RAYCAST_RADIUS = 0.5f;
float Config::RAYCAST_FORCE = 5e3f;

// Graphics parameters
glm::vec2 Config::SCREEN_SIZE = glm::vec2(1366, 768);
float Config::ZOOM_FACTOR = 0.5f;
float Config::ROTATION_ANGLE = 90.0f;
glm::vec3 Config::DEFAULT_CAMERA_POS = glm::vec3(0.0f, 0.0f, 3.0f);

// Physics parameters
float Config::G = 0.1f;
float Config::G_MIN = 0.0f;
float Config::G_MAX = 15.0f;
float Config::G_STEP = 0.01f;

float Config::TIME_STEP = 0.01f;
float Config::TIME_STEP_MIN = 1e-4f;
float Config::TIME_STEP_MAX = 0.5f;
float Config::TIME_STEP_STEP = 1e-4f;

float Config::DAMPING = 0.3f;

float Config::SMOOTHING_RADIUS = 0.4f;
float Config::SMOOTHING_RADIUS_MIN = 0.2f;
float Config::SMOOTHING_RADIUS_MAX = 1.0f;
float Config::SMOOTHING_RADIUS_STEP = 1e-3f;

float Config::REST_DENSITY = 20.0f;
float Config::REST_DENSITY_MIN = 1.0f;
float Config::REST_DENSITY_MAX = 40.0f;
float Config::REST_DENSITY_STEP = 0.1f;

float Config::STIFFNESS = 1.0f;
float Config::STIFFNESS_MIN = 0.0f;
float Config::STIFFNESS_MAX = 25.0f;
float Config::STIFFNESS_STEP = 0.1f;

float Config::VISCOSITY = 1.0f;
float Config::VISCOSITY_MIN = 0.0f;
float Config::VISCOSITY_MAX = 25.0f;
float Config::VISCOSITY_STEP = 0.1f;

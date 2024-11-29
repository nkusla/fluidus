#include "../include/Config.hpp"

glm::vec3 Config::CONTAINER_DIMENSIONS = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec2 Config::SCREEN_SIZE = glm::vec2(1366, 768);
unsigned int Config::SEED = 1616;
float Config::ZOOM_FACTOR = 0.5f;
float Config::ROTATION_ANGLE = 90.0f;
float Config::G = 1e-7f;
float Config::STEP = 0.01f;
int Config::PARTICLE_COUNT = 300;
float Config::DAMPING = 0.3f;
float Config::SMOOTHING_RADIUS = 1.5f;
float Config::REST_DENSITY = 5.0f;
float Config::STIFFNESS_COEFF = 1e-3f;
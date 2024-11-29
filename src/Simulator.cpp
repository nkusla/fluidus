#include "../include/Simulator.hpp"

Simulator::Simulator(
	std::shared_ptr<std::vector<Particle>> particles,
	std::shared_ptr<Container> container) {

	this->particles = particles;
	this->container = container;

	#ifdef _OPENMP
		int num_threads = omp_get_num_procs() / 2;
		omp_set_num_threads(num_threads);
	#endif
}

double Simulator::GetTime() const {
	return time;
}

void Simulator::Reset() {
	time = 0.0;
}

void Simulator::StartStop() {
	stopped = !stopped;
}

void Simulator::Step() {
	if (stopped)
		return;

	CalculateDensities();
	CalculatePressureForces();

	#pragma omp parallel for
	for (auto &p : *particles) {
		p.acceleration += GRAVITY;
		p.velocity += p.acceleration * Config::STEP;
		p.position += p.velocity * Config::STEP;

		CheckWallCollision(p);
	}

	// float a = std::accumulate(particles->begin(), particles->end(), 0.0f,
  //       [](float sum, const Particle& p) {
  //           return sum + glm::length(p.velocity);
  //       }) / static_cast<float>(particles->size());

	// std::cout << "Average velocity: " << a << std::endl;

	time += Config::STEP;
}

void Simulator::CheckWallCollision(Particle &p) {
	glm::vec3 dimensions = container->GetDimensions();
	float lowerBoundY = -dimensions.y / 2.0f;
	float upperBoundY = dimensions.y / 2.0f;
	float lowerBoundX = -dimensions.x / 2.0f;
	float upperBoundX = dimensions.x / 2.0f;
	float lowerBoundZ = -dimensions.z / 2.0f;
	float upperBoundZ = dimensions.z / 2.0f;

	// Check collision with Y walls
	if (p.position.y <= lowerBoundY) {
		p.position.y = lowerBoundY;
		p.velocity.y = -p.velocity.y * Config::DAMPING;
		p.acceleration += GRAVITY;
	} else if (p.position.y >= upperBoundY) {
		p.position.y = upperBoundY;
		p.velocity.y = -p.velocity.y * Config::DAMPING;
		p.acceleration += GRAVITY;
	}

	// Check collision with X walls
	if (p.position.x <= lowerBoundX) {
		p.position.x = lowerBoundX;
		p.velocity.x = -p.velocity.x * Config::DAMPING;
		p.acceleration.x = 0.0f; // Reset other accelerations
	} else if (p.position.x >= upperBoundX) {
		p.position.x = upperBoundX;
		p.velocity.x = -p.velocity.x * Config::DAMPING;
		p.acceleration.x = 0.0f; // Reset other accelerations
	}

	// Check collision with Z walls
	if (p.position.z <= lowerBoundZ) {
		p.position.z = lowerBoundZ;
		p.velocity.z = -p.velocity.z * Config::DAMPING;
		p.acceleration.z = 0.0f; // Reset other accelerations
	} else if (p.position.z >= upperBoundZ) {
		p.position.z = upperBoundZ;
		p.velocity.z = -p.velocity.z * Config::DAMPING;
		p.acceleration.z = 0.0f; // Reset other accelerations
	}
}

void Simulator::CalculateDensities() {

	#pragma omp parallel for
	for(auto &p1 : *particles) {
		p1.density = 0.0f;
		for(auto &p2 : *particles) {
			if (&p1 == &p2)
				continue;

			float distance = glm::distance(p1.position, p2.position);
			p1.density += p2.mass * SpikyKernel(distance, Config::SMOOTHING_RADIUS);
		}
	}
}

void Simulator::CalculatePressureForces() {

	#pragma omp parallel for
	for(auto &p1 : *particles) {
		float pressure1 = LinearEOS(p1);
		glm::vec3 force = glm::vec3(0.0f);

		for(auto &p2 : *particles) {
			if (&p1 == &p2)
				continue;

			float pressure2 = LinearEOS(p2);
			float distance = glm::distance(p1.position, p2.position);
			if (distance == 0.0f || p1.density == 0.0f || p2.density == 0.0f)
				continue;

			glm::vec3 direction = glm::normalize(p1.position - p2.position);
			float force = -p2.mass * (pressure1 + pressure2) / (2.0f * p2.density) * SpikyKernelDeriv(distance, Config::SMOOTHING_RADIUS);
			p1.acceleration += force * direction / p1.density;
		}
	}
}

inline float Simulator::LinearEOS(Particle &p) {
	return Config::STIFFNESS_COEFF * (p.density - Config::REST_DENSITY);
}
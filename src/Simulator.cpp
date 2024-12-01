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

	#pragma omp parallel for
	for (auto &p : *particles) {
		CalculateDensity(p);
	}

	#pragma omp parallel for
	for (auto &p : *particles) {
		if (p.density == 0)
			continue;

		glm::vec3 pressureForce = CalculatePressureForces(p);
		p.velocity += pressureForce / p.density * Config::TIME_STEP;
	}

	#pragma omp parallel for
	for (auto &p : *particles) {
		if (p.density == 0)
			continue;

		glm::vec3 viscosityForce = CalculateViscosityForces(p);
		p.velocity += viscosityForce / p.density * Config::TIME_STEP;
	}

	#pragma omp parallel for
	for (auto &p : *particles) {
		p.velocity += GRAVITY * Config::TIME_STEP;
		p.position += p.velocity * Config::TIME_STEP;

		CheckWallCollision(p);
	}

	time += Config::TIME_STEP;
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

void Simulator::CalculateDensity(Particle &p) {
	p.density = 0.0f;

	for(auto &p2 : *particles) {
		if(&p == &p2)
			continue;

		float distance = glm::distance(p.position, p2.position);
		p.density += p2.mass * SpikyKernel(distance, Config::SMOOTHING_RADIUS);
	}
}

glm::vec3 Simulator::CalculatePressureForces(const Particle &p) {
	float pressure = LinearEOS(p);
	glm::vec3 pressureForce = glm::vec3(0.0f);

	for(auto &p2 : *particles) {
		if (&p == &p2)
			continue;

		float distance = glm::distance(p.position, p2.position);
		if(distance == 0 || p2.density == 0)
			continue;

		float pressure2 = LinearEOS(p2);

		glm::vec3 direction = glm::normalize(p.position - p2.position);
		float force = -p2.mass * (pressure + pressure2) / (2.0f * p2.density) * SpikyKernelDeriv(distance, Config::SMOOTHING_RADIUS);
		pressureForce += force * direction;
	}

	return pressureForce;
}

glm::vec3 Simulator::CalculateViscosityForces(const Particle &p) {
	glm::vec3 viscosityForce = glm::vec3(0.0f);

	for(auto &p2 : *particles) {
		if (&p == &p2)
			continue;

		float distance = glm::distance(p.position, p2.position);
		if(distance == 0 || p2.density == 0)
			continue;

		glm::vec3 relativeVelocity = p2.velocity - p.velocity;
		viscosityForce += p2.mass * relativeVelocity / p2.density * ViscosityKernelLaplacian(distance, Config::SMOOTHING_RADIUS);
	}

	return viscosityForce * Config::VISCOSITY;
}

inline float Simulator::LinearEOS(const Particle &p) {
	return Config::STIFFNESS * (p.density - Config::REST_DENSITY);
}
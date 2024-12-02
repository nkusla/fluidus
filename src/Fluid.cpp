#include "../include/Fluid.hpp"

Fluid::Fluid() {
	particles = std::make_shared<std::vector<Particle>>(Config::PARTICLE_COUNT);

	GenerateRandParticles(Config::PARTICLE_COUNT);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, particles->size() * sizeof(Particle), particles->data(), GL_DYNAMIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, position));
	glEnableVertexAttribArray(0);

	// Velocity attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));
	glEnableVertexAttribArray(1);

	// Force attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, force));
	glEnableVertexAttribArray(2);

	// Mass attribute
	glVertexAttribPointer(3, 1, GL_DOUBLE, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, mass));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram = ShaderLoader::LoadShaders(
		"../glsl/fluid.vert.glsl",
		"../glsl/fluid.frag.glsl"
		// "../glsl/fluid.geom.glsl"
	);
}

std::shared_ptr<std::vector<Particle>> Fluid::GetParticles() {
	return particles;
}

void Fluid::GenerateRandParticles(int count) {
	std::mt19937 gen(Config::SEED);
	std::uniform_real_distribution<float> dis(-0.5f, 0.5f);

	for (auto &particle : *particles) {
		particle.position = glm::vec3(dis(gen), dis(gen), dis(gen));
		//particle.velocity = glm::vec3(dis(gen), dis(gen), dis(gen));
		particle.velocity = glm::vec3(0.0f);
		particle.force = glm::vec3(0.0f);
		particle.mass = 1.0f;
	}
}

void Fluid::Render(const glm::mat4 &view, const glm::mat4 &projection) {
	glUseProgram(shaderProgram);

	glm::mat4 MVP = projection * view * model;
	GLuint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, particles->size());
	glBindVertexArray(0);

	glUseProgram(0);
}

void Fluid::UpdateVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, particles->size() * sizeof(Particle), particles->data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
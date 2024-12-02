#include "../include/Container.hpp"

Container::Container(glm::vec3 dimensions) : dimensions(dimensions) {
	float width = dimensions.x;
	float height = dimensions.y;
	float depth = dimensions.z;

	DefineVerticies();

	indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		0, 4, 7, 7, 3, 0,
		// Right face
		1, 5, 6, 6, 2, 1,
		// Top face
		3, 2, 6, 6, 7, 3,
		// Bottom face
		0, 1, 5, 5, 4, 0
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram = ShaderLoader::LoadShaders(
		"../glsl/container.vert.glsl",
		"../glsl/container.frag.glsl"
	);
}

void Container::DefineVerticies() {
	float width = dimensions.x;
	float height = dimensions.y;
	float depth = dimensions.z;

	vertices = {
		// Front face
		-width / 2, -height / 2, depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		width / 2, -height / 2, depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		width / 2,  height / 2, depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		-width / 2,  height / 2, depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,

		// Back face
		-width / 2, -height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		width / 2, -height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		width / 2,  height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f,
		-width / 2,  height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f
	};
}

glm::vec3 Container::GetDimensions() const {
	return dimensions;
}

void Container::UpdateDimensions(glm::vec3 newDimensions) {
	dimensions = newDimensions;
	DefineVerticies();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Container::Render(const glm::mat4 &view, const glm::mat4 &projection) {
	glUseProgram(shaderProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 MVP = projection * view * model;
	GLuint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUseProgram(0);
}

void Container::UpdateVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
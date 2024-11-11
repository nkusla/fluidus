#include "../include/Container.hpp"

Container::Container(float width, float height, float depth)
	: width(width), height(height), depth(depth) {

	model = glm::mat4(1.0f);

		float vertices[] = {
			// Front face
			-width / 2, -height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			 width / 2, -height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			 width / 2,  height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			-width / 2,  height / 2, -depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha

			// Back face
			-width / 2, -height / 2,  depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			 width / 2, -height / 2,  depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			 width / 2,  height / 2,  depth / 2, 1.0f, 1.0f, 1.0f, 0.5f, // White with 50% alpha
			-width / 2,  height / 2,  depth / 2, 1.0f, 1.0f, 1.0f, 0.5f  // White with 50% alpha
		};

    unsigned int indices[] = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram = ShaderLoader::loadShaders(
		"../glsl/vertex_shader.glsl",
		"../glsl/fragment_shader.glsl"
	);
}

Container::~Container() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}

float Container::getWidth() const { return width; }
float Container::getHeight() const { return height; }
float Container::getDepth() const { return depth; }

void Container::render(const glm::mat4 &view, const glm::mat4 &projection) {
	glUseProgram(shaderProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
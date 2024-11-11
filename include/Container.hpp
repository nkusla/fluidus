#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.hpp"

class Container {
	private:
		float width, height, depth;
		GLuint VAO, VBO, EBO;
		GLuint shaderProgram;

		glm::mat4 model;
	public:
		Container();
		Container(float width, float height, float depth);
		~Container();

		float getWidth() const;
		float getHeight() const;
		float getDepth() const;

		void render(const glm::mat4 &view, const glm::mat4 &projection);
};

#endif
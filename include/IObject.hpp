#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

class IObject {
	protected:
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint EBO = 0;
		GLuint shaderProgram = 0;
		glm::mat4 model = glm::mat4(1.0f);

	public:
		virtual void render(const glm::mat4 &view, const glm::mat4 &projection) = 0;

		virtual void updateVBO() = 0;

		virtual ~IObject() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteProgram(shaderProgram);
		}
};

#endif // IOBJECT_HPP
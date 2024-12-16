#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class IObject {
	protected:
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint EBO = 0;
		GLuint selectedProgram = 0;
		glm::mat4 model = glm::mat4(1.0f);
		std::unordered_map<const char*, GLuint> shaderPrograms;

	public:
		virtual void Render(const glm::mat4 &view, const glm::mat4 &projection) = 0;

		virtual void UpdateVBO() = 0;

		virtual void SelectShaderProgram(const char* name = nullptr);
		virtual std::vector<const char*> GetShaderProgramNames();

		virtual ~IObject();
};

#endif // IOBJECT_HPP
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.hpp"
#include "IObject.hpp"

class Container : public IObject {
	private:
		glm::vec3 dimensions;

		std::array<float, 56> vertices;
		std::array<unsigned int, 36> indices;

		void DefineVerticies();
	public:
		Container(glm::vec3 dimensions);
		~Container() = default;

		void UpdateDimensions(glm::vec3 newDimensions);
		glm::vec3 GetDimensions() const;

		void Render(const glm::mat4 &view, const glm::mat4 &projection) override;
		void UpdateVBO() override;
};

#endif
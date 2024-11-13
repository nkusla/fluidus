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

		glm::mat4 model;
		std::array<float, 56> vertices;
		std::array<unsigned int, 36> indices;

		void defineVerticies();
	public:
		Container(glm::vec3 dimensions);
		~Container();

		void updateDimensions(glm::vec3 newDimensions);
		glm::vec3 getDimensions() const;

		void render(const glm::mat4 &view, const glm::mat4 &projection) override;
};

#endif
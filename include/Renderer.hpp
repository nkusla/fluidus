#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Container.hpp"

class Renderer {
	private:
		glm::mat4 projection;
		glm::mat4 view;
		float angle = 0.0f;

		std::shared_ptr<Container> container = nullptr;

	public:
		Renderer(float aspectRatio);
		void render();

		void setContainer(std::shared_ptr<Container> container);
		std::shared_ptr<Container> getContainer() const;
		void rotateCamera(float angleOffset, glm::vec3 axis);
		void zoomCamera(float zoomOffset);
		void initCamera();
};

#endif
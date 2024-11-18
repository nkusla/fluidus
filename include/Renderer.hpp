#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Container.hpp"
#include "Fluid.hpp"

class Renderer {
	private:
		glm::mat4 projection;
		glm::mat4 view;

	public:
		std::shared_ptr<Container> container = nullptr;
		std::shared_ptr<Fluid> fluid = nullptr;

		Renderer(float aspectRatio);
		void Render();

		void RotateCamera(float angleOffset, glm::vec3 axis);
		void ZoomCamera(float zoomOffset);
		void InitCamera();
};

#endif
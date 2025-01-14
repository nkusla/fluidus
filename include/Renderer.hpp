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
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	public:
		std::shared_ptr<Container> container = nullptr;
		std::shared_ptr<Fluid> fluid = nullptr;

		Renderer(float aspectRatio);
		void Render();

		glm::vec3 CalcRayDir(glm::vec2 mousePos, glm::vec2 screenSize);
		glm::vec3 CastRay(glm::vec2 mousePos, glm::vec2 screenSize);
		void RotateCamera(float angleOffset, glm::vec3 axis);
		void ZoomCamera(float zoomOffset);
		void CenterCamera();
};

#endif
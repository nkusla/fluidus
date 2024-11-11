#include "../include/Renderer.hpp"

Renderer::Renderer(float aspectRatio) {
	projection = glm::perspective(
		glm::radians(45.0f), 						// Field of view
		aspectRatio,										// Aspect ratio
		0.1f,														// Near clipping plane
		200.0f);												// Far clipping plane

	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f),	// Camera position
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera target
		glm::vec3(0.0f, 1.0f, 0.0f)		// Up vector
	);
}

void Renderer::setContainer(std::shared_ptr<Container> container) {
	this->container = container;
}

void Renderer::rotateHorizontalCamera(float angleOffset) {
	angle += angleOffset;

	glm::vec3 cameraPos = glm::vec3(view[3]);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 newCameraPos = glm::vec3(rotation * glm::vec4(cameraPos, 1.0f));

	view = glm::lookAt(newCameraPos, cameraTarget, up);
}

void Renderer::rotateVerticalCamera(float angleOffset) {
	angle += angleOffset;

	glm::vec3 cameraPos = glm::vec3(view[3]);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 newCameraPos = glm::vec3(rotation * glm::vec4(cameraPos, 1.0f));

	view = glm::lookAt(newCameraPos, cameraTarget, up);
}

void Renderer::render() {
	container->render(view, projection);
}

#include "../include/Renderer.hpp"

Renderer::Renderer(float aspectRatio) {
	projection = glm::perspective(
		glm::radians(45.0f), 						// Field of view
		aspectRatio,										// Aspect ratio
		0.1f,														// Near clipping plane
		200.0f);												// Far clipping plane

	initCamera();
}

void Renderer::initCamera() {
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f),	// Camera position (eye)
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera target
		glm::vec3(0.0f, 1.0f, 0.0f)		// Up vector
	);
}

void Renderer::rotateCamera(float angleOffset, glm::vec3 axis) {
    glm::mat4 translationToOrigin = glm::translate(glm::mat4(1.0f), -glm::vec3(view[3]));
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleOffset), axis);
    glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), glm::vec3(view[3]));

    view = translationBack * rotation * translationToOrigin * view;
}

void Renderer::zoomCamera(float zoomOffset) {
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zoomOffset));
		view = translation * view;
}

void Renderer::render() {
	container->render(view, projection);
}

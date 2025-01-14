#include "../include/Renderer.hpp"

Renderer::Renderer(float aspectRatio) {
	projection = glm::perspective(
		glm::radians(45.0f), 						// Field of view
		aspectRatio,										// Aspect ratio
		0.1f,														// Near clipping plane
		200.0f);												// Far clipping plane

	view = glm::lookAt(
		cameraPos,										// Camera position (eye)
		glm::vec3(0.0f, 0.0f, 0.0f),	// Camera target
		glm::vec3(0.0f, 1.0f, 0.0f)		// Up vector
	);
}

void Renderer::RotateCamera(float angleOffset, glm::vec3 axis) {
    glm::mat4 translationToOrigin = glm::translate(glm::mat4(1.0f), -glm::vec3(view[3]));
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleOffset), axis);
    glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), glm::vec3(view[3]));

    view = translationBack * rotation * translationToOrigin * view;

		glm::mat4 invView = glm::inverse(view);
		cameraPos = glm::vec3(invView[3]);
}

void Renderer::ZoomCamera(float zoomOffset) {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zoomOffset));
	view = translation * view;
}

void Renderer::CenterCamera() {
	cameraPos = Config::DEFAULT_CAMERA_POS;
	view = glm::lookAt(
		cameraPos,															// Camera position (eye)
		glm::vec3(0.0f, 0.0f, 0.0f),						// Camera target
		glm::vec3(0.0f, 1.0f, 0.0f)							// Up vector
	);
}

glm::vec3 Renderer::CalcRayDir(glm::vec2 mousePos, glm::vec2 screenSize) {
	float normX = (2.0f * mousePos.x) / screenSize.x - 1.0f;
	float normY = 1.0f - (2.0f * mousePos.y) / screenSize.y;
	glm::vec4 clipCoords(normX, normY, -1.0f, 1.0f);

	glm::vec4 eyeCoords = glm::inverse(projection) * clipCoords;
	eyeCoords.z = -1.0f;
	eyeCoords.w = 0.0f;

	glm::vec3 rayWorld = glm::vec3(glm::inverse(view) * eyeCoords);
	rayWorld = glm::normalize(rayWorld);

	return rayWorld;
}

glm::vec3 Renderer::CastRay(glm::vec2 mousePos, glm::vec2 screenSize) {
	glm::vec3 rayDir = CalcRayDir(mousePos, screenSize);
	glm::vec3 rayOrigin = cameraPos;
	glm::vec3 containerDimensions = container->GetDimensions();

	glm::vec3 containerMin = -containerDimensions / 2.0f;
	glm::vec3 containerMax = containerDimensions / 2.0f;

	glm::vec3 t1 = (containerMin - rayOrigin) / rayDir;
	glm::vec3 t2 = (containerMax - rayOrigin) / rayDir;

	glm::vec3 tMin = glm::min(t1, t2);
	glm::vec3 tMax = glm::max(t1, t2);

	float tNear = glm::max(glm::max(tMin.x, tMin.y), tMin.z);
  float tFar = glm::min(glm::min(tMax.x, tMax.y), tMax.z);

	if (tNear > tFar || tFar < 0)
		return glm::vec3(INFINITY);

  return tNear * rayDir + rayOrigin;
}

void Renderer::Render() {
	fluid->UpdateVBO();

	container->Render(view, projection);
	fluid->Render(view, projection);
}

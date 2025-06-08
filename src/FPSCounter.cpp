#include "../include/FPSCounter.hpp"

FPSCounter::FPSCounter(double targetFPS)
: frameCount(0),
	fps(0.0),
	lastFPSTime(glfwGetTime()),
	lastFrameTime(glfwGetTime()),
	targetFrameTime(1.0 / targetFPS) {}

void FPSCounter::Update() {
	double currentTime = glfwGetTime();
	frameCount++;

	// Calculate FPS every second
	if(currentTime - lastFPSTime >= 1.0) {
		fps = frameCount / (currentTime - lastFPSTime);
		frameCount = 0;
		lastFPSTime = currentTime;
	}

	// Calculate frame time and sleep if necessary to maintain target FPS
	double frameTime = currentTime - lastFrameTime;

	if (frameTime < targetFrameTime) {
			// Sleep for the remaining time to achieve ~60 FPS
			double sleepTime = targetFrameTime - frameTime;
			std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));

			currentTime = glfwGetTime();
	}

	lastFrameTime = currentTime;
}
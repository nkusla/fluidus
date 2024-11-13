#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <memory>
#include "Renderer.hpp"
#include "Config.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window = nullptr;
		glm::vec2 screenSize;
		double lastKeyPressTime = 0.0;
		double lastFPSTime = 0.0;
		int frameCount = 0;
		float fps = 0.0f;

		void InitImGui();
	public:
		std::shared_ptr<Renderer> renderer = nullptr;

		ApplicationWindow(glm::vec2 screenSize);
		~ApplicationWindow();

		GLFWwindow* getWindow();

		bool checkClose();
		void checKeyPressed();
		void displayAllWidgets();
		void runFrame();
		void updateFPS();

		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
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

class ApplicationWindow {
	private:
		GLFWwindow* window;
		glm::vec2 screenSize;

		std::shared_ptr<Renderer> renderer = nullptr;

		void InitImGui();

	public:
		ApplicationWindow(glm::vec2 screenSize);
		~ApplicationWindow();

		GLFWwindow* getWindow();
		void setRenderer(std::shared_ptr<Renderer> renderer);

		bool checkClose();
		void checKeyPressed();
		void displayAllWidgets();
		void runFrame();
};

#endif
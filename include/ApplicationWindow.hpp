#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <iostream>
#include "Container.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window;
		glm::vec2 screenSize;

		glm::mat4 projection;
		glm::mat4 view;

		Container container;

		void InitImGui();

	public:
		ApplicationWindow(int width, int height);
		GLFWwindow* getWindow();

		bool checkClose();
		void close();
		void checKeyPressed();
		void displayAllWidgets();
		void runFrame();
};

#endif
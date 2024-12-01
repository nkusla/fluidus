#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include "Renderer.hpp"
#include "Config.hpp"
#include "Simulator.hpp"

class ApplicationWindow {
	private:
		GLFWwindow* window = nullptr;
		glm::vec2 screenSize;

		double lastKeyPressTime = 0.0;
		double lastFPSTime = 0.0;
		int frameCount = 0;
		float fps = 0.0f;

		bool spacePressed = false;
		bool HPressed = false;
		bool hideWidgets = false;

		void InitImGui();
	public:
		std::shared_ptr<Renderer> renderer = nullptr;
		std::shared_ptr<Simulator> simulator = nullptr;

		ApplicationWindow(glm::vec2 screenSize);
		~ApplicationWindow();

		GLFWwindow* GetWindow();

		bool CheckClose();
		void ChecKeyPressed();
		void DisplayAllWidgets();
		void DisplayParametersWidgets();
		void DisplayPhysicsParams();
		void DisplayInfoWidgets();
		void RunFrame();
		void UpdateFPS();
		void PrintOpenGLInfo();

		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
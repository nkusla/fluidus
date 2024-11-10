#include "../include/ApplicationWindow.hpp"

ApplicationWindow::ApplicationWindow(int width, int height) {
	if(!glfwInit()) {
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	glfwSetErrorCallback(
		[](int error, const char *description) {
			std::cerr << "\033[1;31mError:\033[0m " << description << std::endl;
		}
	);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

	screenSize = {width, height};
	window = glfwCreateWindow(width, height, "Fluidus", NULL, NULL);

	if(window == NULL) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
  }

	InitImGui();
}

void ApplicationWindow::InitImGui() {
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
		std::cerr << "Failed to initialize ImGui GLFW implementation" << std::endl;
		return;
	}

	if (!ImGui_ImplOpenGL3_Init("#version 330")) {
		std::cerr << "Failed to initialize ImGui OpenGL implementation" << std::endl;
		return;
	}
}

GLFWwindow* ApplicationWindow::getWindow() { return window; }

bool ApplicationWindow::checkClose() {
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}

void ApplicationWindow::close() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void ApplicationWindow::checKeyPressed() {
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		std::cout << "Arrow down pressed" << std::endl;
	}
}

void ApplicationWindow::displayAllWidgets() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("##Control", nullptr, ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(screenSize.x - 200, 0));
	ImGui::SetWindowSize(ImVec2(200, 370));

	ImGui::Text("Hello, world!");
	// Widgets go here ...

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ApplicationWindow::runFrame() {
	displayAllWidgets();


	glfwSwapBuffers(window);
	glfwPollEvents();
};
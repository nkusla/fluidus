#include "../include/ApplicationWindow.hpp"

ApplicationWindow::ApplicationWindow(glm::vec2 screenSize) : screenSize(screenSize) {

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

	window = glfwCreateWindow(screenSize.x, screenSize.y, "Fluidus", NULL, NULL);

	if(window == NULL) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
  }

	glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitImGui();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetWindowUserPointer(window, static_cast<void*>(this));
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

ApplicationWindow::~ApplicationWindow() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* ApplicationWindow::getWindow() { return window; }

void ApplicationWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	ApplicationWindow* appWindow = static_cast<ApplicationWindow*>(glfwGetWindowUserPointer(window));
	appWindow->renderer->zoomCamera(yoffset * Config::ZOOM_FACTOR);
}

bool ApplicationWindow::checkClose() {
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}

void ApplicationWindow::checKeyPressed() {
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastKeyPressTime;
	lastKeyPressTime = currentTime;

	float rotationAngle = Config::ROTATION_ANGLE * deltaTime;

	if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		renderer->initCamera();
	}
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		renderer->rotateCamera(rotationAngle, X_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		renderer->rotateCamera(-rotationAngle, X_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		renderer->rotateCamera(-rotationAngle, Y_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		renderer->rotateCamera(rotationAngle, Y_AXIS);
	}
}

void ApplicationWindow::displayAllWidgets() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(screenSize.x - 250, 0));
	ImGui::SetWindowSize(ImVec2(250, 380));

	ImGui::Text("Container dimensions");
	bool widthChanged = ImGui::SliderFloat("Width", &Config::CONTAINER_DIMENSIONS.x, 1.0f, 3.0f);
	bool heightChanged = ImGui::SliderFloat("Heigth", &Config::CONTAINER_DIMENSIONS.y, 1.0f, 3.0f);
	bool depthChanged = ImGui::SliderFloat("Depth", &Config::CONTAINER_DIMENSIONS.z, 1.0f, 3.0f);

	if(widthChanged || heightChanged || depthChanged)
		renderer->container->updateDimensions(Config::CONTAINER_DIMENSIONS);

	ImGui::Spacing();
	ImGui::Text("FPS: %.2f", fps);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ApplicationWindow::runFrame() {
	updateFPS();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayAllWidgets();

	simulator->step();
	renderer->render();

	glfwSwapBuffers(window);
	glfwPollEvents();
};

void ApplicationWindow::updateFPS() {
	double currentTime = glfwGetTime();
	frameCount++;

	if(currentTime - lastFPSTime >= 1.0) {
		fps = frameCount / (currentTime - lastFPSTime);
		frameCount = 0;
		lastFPSTime = currentTime;
	}
}
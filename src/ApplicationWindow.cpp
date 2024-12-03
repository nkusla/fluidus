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
	glEnable(GL_PROGRAM_POINT_SIZE);

	InitImGui();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetWindowUserPointer(window, static_cast<void*>(this));

	#ifdef DEBUG
		PrintOpenGLInfo();
	#endif
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

GLFWwindow* ApplicationWindow::GetWindow() { return window; }

void ApplicationWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	ApplicationWindow* appWindow = static_cast<ApplicationWindow*>(glfwGetWindowUserPointer(window));
	appWindow->renderer->ZoomCamera(yoffset * Config::ZOOM_FACTOR);
}

bool ApplicationWindow::CheckClose() {
	return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}

void ApplicationWindow::ChecKeyPressed() {
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastKeyPressTime;
	lastKeyPressTime = currentTime;

	float rotationAngle = Config::ROTATION_ANGLE * deltaTime;

	if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		renderer->CenterCamera();
	}

	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		simulator->Reset();
		renderer->fluid->GenerateRandParticles(Config::PARTICLE_COUNT);
	}

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		renderer->RotateCamera(rotationAngle, X_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		renderer->RotateCamera(-rotationAngle, X_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		renderer->RotateCamera(-rotationAngle, Y_AXIS);
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		renderer->RotateCamera(rotationAngle, Y_AXIS);
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if(!StopPressed) {
			simulator->StartStop();
			StopPressed = true;
		}
	}
	else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		StopPressed = false;
	}

	if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		if(!HidePressed) {
			hideWidgets = !hideWidgets;
			HidePressed = true;
		}
	}
	else if(glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE) {
		HidePressed = false;
	}

	StepPressed = (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) ? true : false;
}

void ApplicationWindow::DisplayAllWidgets() {
	if(hideWidgets)
		return;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	DisplayParametersWidgets();
	DisplayInfoWidgets();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ApplicationWindow::DisplayParametersWidgets() {
	ImGui::Begin("Parameters", nullptr,
		ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize);

	ImGui::SetWindowPos(ImVec2(screenSize.x - 250, 0));
	ImGui::SetWindowSize(ImVec2(250, 380));

	ImGui::Text("Particles count: %ld", renderer->fluid->GetParticles()->size());

	ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Container dimensions");
	ImGui::Spacing(); ImGui::Spacing();

	bool widthChanged = ImGui::SliderFloat("Width", &Config::CONTAINER_DIMENSIONS.x, Config::CONTAINER_DIMENSIONS_MIN, Config::CONTAINER_DIMENSIONS_MAX);
	bool heightChanged = ImGui::SliderFloat("Heigth", &Config::CONTAINER_DIMENSIONS.y, Config::CONTAINER_DIMENSIONS_MIN, Config::CONTAINER_DIMENSIONS_MAX);
	bool depthChanged = ImGui::SliderFloat("Depth", &Config::CONTAINER_DIMENSIONS.z, Config::CONTAINER_DIMENSIONS_MIN, Config::CONTAINER_DIMENSIONS_MAX);

	if(widthChanged || heightChanged || depthChanged)
		renderer->container->UpdateDimensions(Config::CONTAINER_DIMENSIONS);

	ImGui::Spacing(); ImGui::Spacing();
	ImGui::DragScalar("Time step", ImGuiDataType_Float,
		&Config::TIME_STEP,
		Config::TIME_STEP_STEP,
		&Config::TIME_STEP_MIN,
		&Config::TIME_STEP_MAX, "%.4f");

	DisplayPhysicsParams();

	ImGui::End();
}

void ApplicationWindow::DisplayPhysicsParams() {
	ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Physics parameters");
	ImGui::Spacing(); ImGui::Spacing();

	ImGui::PushItemWidth(100);
	ImGui::DragScalar("Gravity", ImGuiDataType_Float,
		&Config::G,
		Config::G_STEP,
		&Config::G_MIN,
		&Config::G_MAX, "%.2f");

	ImGui::DragScalar("Smoothing radius", ImGuiDataType_Float,
		&Config::SMOOTHING_RADIUS,
		Config::SMOOTHING_RADIUS_STEP,
		&Config::SMOOTHING_RADIUS_MIN,
		&Config::SMOOTHING_RADIUS_MAX, "%.2f");

	ImGui::DragScalar("Rest density", ImGuiDataType_Float,
		&Config::REST_DENSITY,
		Config::REST_DENSITY_STEP,
		&Config::REST_DENSITY_MIN,
		&Config::REST_DENSITY_MAX, "%.1f");

	ImGui::DragScalar("Stiffness", ImGuiDataType_Float,
		&Config::STIFFNESS,
		Config::STIFFNESS_STEP,
		&Config::STIFFNESS_MIN,
		&Config::STIFFNESS_MAX, "%.1f");

	ImGui::DragScalar("Viscosity", ImGuiDataType_Float,
		&Config::VISCOSITY,
		Config::VISCOSITY_STEP,
		&Config::VISCOSITY_MIN,
		&Config::VISCOSITY_MAX, "%.1f");

	ImGui::PopItemWidth();
}

void ApplicationWindow::DisplayInfoWidgets() {
	ImGui::Begin("Info", nullptr,
		ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoBackground);

	ImGui::SetWindowPos(ImVec2(screenSize.x - 110, screenSize.y - 70));
	ImGui::SetWindowSize(ImVec2(110, 70));

	ImGui::Text("FPS: %.2f", fps);
	ImGui::Spacing(); ImGui::Spacing();
	ImGui::Text("Time: %.2f", simulator->GetTime());
	ImGui::Spacing(); ImGui::Spacing();

	ImGui::End();
}

void ApplicationWindow::RunFrame() {
	UpdateFPS();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DisplayAllWidgets();

	simulator->Step(StepPressed);
	renderer->Render();

	glfwSwapBuffers(window);
	glfwPollEvents();
};

void ApplicationWindow::UpdateFPS() {
	double currentTime = glfwGetTime();
	frameCount++;

	if(currentTime - lastFPSTime >= 1.0) {
		fps = frameCount / (currentTime - lastFPSTime);
		frameCount = 0;
		lastFPSTime = currentTime;
	}
}

void ApplicationWindow::PrintOpenGLInfo() {
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	std::cout << "\033[1;33mOpenGL summary\033[0m" << std::endl;
	std::cout << "  OpenGL Renderer: " << renderer << std::endl;
	std::cout << "  OpenGL Vendor: " << vendor << std::endl;
	std::cout << "  OpenGL Version: " << version << std::endl;
	std::cout << "  GLSL Version: " << glslVersion << std::endl;
	std::cout << "  OpenGL Version (integer): " << major << "." << minor << std::endl;

	GLint output;
	std::cout << std::endl;
	std::cout << "\033[1;33mGeometry shader\033[0m" << std::endl;
	glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &output);
	std::cout << "  GL_MAX_GEOMETRY_OUTPUT_VERTICES: " << output << std::endl;

	glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &output);
	std::cout << "  GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS: " << output << std::endl;

	glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, &output);
	std::cout << "  GL_MAX_GEOMETRY_OUTPUT_COMPONENTS: " << output << std::endl;
}
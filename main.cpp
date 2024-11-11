#include "include/ApplicationWindow.hpp"
#include "include/Container.hpp"

int main() {
	ApplicationWindow appWindow(1366, 768);
	float aspectRatio = 1366.0f / 768.0f;
	auto renderer = std::make_shared<Renderer>(aspectRatio);
	appWindow.setRenderer(renderer);

	auto container = std::make_shared<Container>(2.0f, 1.0f, 1.0f);
	renderer->setContainer(container);

	while(appWindow.checkClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	return 0;
}
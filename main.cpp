#include "include/ApplicationWindow.hpp"
#include "include/Container.hpp"
#include "include/Config.hpp"

int main() {
	ApplicationWindow appWindow(Config::SCREEN_SIZE);
	float aspectRatio = Config::SCREEN_SIZE.x / Config::SCREEN_SIZE.y;

	auto renderer = std::make_shared<Renderer>(aspectRatio);
	renderer->container = std::make_shared<Container>(Config::CONTAINER_DIMENSIONS);
	renderer->fluid = std::make_shared<Fluid>();
	appWindow.renderer = renderer;

	while(appWindow.checkClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	return 0;
}
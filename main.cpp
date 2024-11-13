#include "include/ApplicationWindow.hpp"
#include "include/Container.hpp"
#include "include/Config.hpp"

int main() {
	ApplicationWindow appWindow(Config::SCREEN_SIZE);
	float aspectRatio = Config::SCREEN_SIZE.x / Config::SCREEN_SIZE.y;

	appWindow.renderer = std::make_shared<Renderer>(aspectRatio);
	appWindow.renderer->container = std::make_shared<Container>(Config::CONTAINER_DIMENSIONS);

	while(appWindow.checkClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	return 0;
}
#include "include/ApplicationWindow.hpp"

int main() {
	ApplicationWindow appWindow(1366, 768);

	auto container = std::make_shared<Container>(2.0f, 1.0f, 1.0f);

	appWindow.setContent(container);

	while(appWindow.checkClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	return 0;
}
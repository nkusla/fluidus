#include "include/ApplicationWindow.hpp"

int main() {
	ApplicationWindow appWindow(1366, 768);

	while(appWindow.checkClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	appWindow.close();

	return 0;
}
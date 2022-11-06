#include "Window.h"

int main() {
	
	//init srand
	std::srand(static_cast<unsigned>(time(NULL)));
	
	//create window
	Window window;
	while (window.running())
	{
		window.update();
		window.render();
	}

	return 0;
}
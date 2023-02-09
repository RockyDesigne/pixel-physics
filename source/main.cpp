#include "Window.h"

int main() {
	
	//create window
	window window;
	while (window.running())
	{
		window.update();
		window.render();
	}

	return 0;
}
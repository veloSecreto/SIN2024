#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include <iostream>

namespace Editor {

	void init() {
		std::cout << "Editor is initialized" << std::endl;
	}

	void update() {
		if (Input::mouseButtonDown(SIN_MOUSE_BUTTON_RIGHT)) {
	        Input::disableCursor();
	        Camera::update();
	    }
	    else {
	        Input::unhideCursor();
	    }
	}
};
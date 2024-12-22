#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include "../game/game.h"
#include "../api/opengl/gl_renderer.h"
#include "gizmo.hpp"
#include <iostream>

namespace Editor {
	DebugMode debugMode = DebugMode::NONE;
	void init() {
		Gizmo::init();
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

		if (Input::keyPressed(SIN_KEY_R))
		{
			OpenGLRenderer::_renderModeChanged = true;
			OpenGLRenderer::renderMode = OpenGLRenderer::renderMode == RenderMode::FORWARD ? RenderMode::DEFERRED : RenderMode::FORWARD;
			std::cout << "Render Mode switched to " << (OpenGLRenderer::renderMode == RenderMode::FORWARD ? "Forward" : "Deferred") << " rendering" << std::endl;
		}
		else OpenGLRenderer::_renderModeChanged = false;

		if (Input::keyPressed(SIN_KEY_L)) {
			debugMode = (DebugMode)(((int)debugMode + 1) % 2);
		}

		Game::scene.gameObjects[3].transform = Gizmo::update(Game::scene.gameObjects[3].transform.to_mat4());
	}
};

void Editor::draw() {
	Gizmo::draw();
	if (debugMode == DebugMode::AABB) {
		OpenGLRenderer::debugAABBs();
	}
}
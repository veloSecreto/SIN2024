#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include "../game/game.h"
#include "../api/opengl/gl_renderer.h"
#include "gizmo.hpp"
#include <iostream>

namespace Editor {
	glm::mat4 m_model;

	void init() {
		Gizmo::init();
		m_model = glm::mat4(1);
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

		Game::scene.gameObjects[0].transform = Gizmo::update(Game::scene.gameObjects[0].transform.to_mat4());
		Gizmo::draw();
	}
};
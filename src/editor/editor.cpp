#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include "../game/game.h"
#include "../api/opengl/gl_renderer.h"
#include "gizmo.hpp"
#include "../physics/physics.h"
#include "../file/file_system.h"

namespace Editor {
	DebugMode debugMode = DebugMode::NONE;
	int g_selectionIndex;

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

		if (Input::mouseButtonPressed(SIN_MOUSE_BUTTON_LEFT) && !Gizmo::hasHover())
		{
			float nearestDistance = std::numeric_limits<float>::max();
			int closestObjectIndex = -1;

			for (unsigned int i = 0; i < Game::scene.gameObjects.size(); ++i) {

				Ray mouseRay = { Camera::m_position, Input::getMouseRay() };
				AABB& aabb = Game::scene.gameObjects[i].aabb;
				float tMin;

				bool hit = Physics::intersection(mouseRay, aabb, tMin);
				if (hit && tMin < nearestDistance) {
					nearestDistance = tMin;
					closestObjectIndex = i;
				}
			}
			
			g_selectionIndex = closestObjectIndex;
		}

		// saving scene data
		if (Input::keyDown(SIN_KEY_LEFT_CONTROL) && Input::keyDown(SIN_KEY_LEFT_SHIFT) && Input::keyPressed(SIN_KEY_S)) {
			FileSystem::Repository::saveSceneData();
		}

		if (g_selectionIndex != -1)
		{
			Gizmo::update(Game::scene.gameObjects[g_selectionIndex].transform);
		}
	}
};

void Editor::draw() {
	if (g_selectionIndex != -1) Gizmo::draw();
	if (debugMode == DebugMode::AABB) {
		OpenGLRenderer::debugAABBs();
	}
}
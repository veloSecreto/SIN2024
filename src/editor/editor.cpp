#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include "../game/game.h"
#include "../api/opengl/gl_renderer.h"
#include "../api/opengl/gl_backend.h"
#include "gizmo.hpp"
#include "../physics/physics.h"
#include "../file/file_system.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>



namespace Editor {

	struct ClipBoard {
		bool copied = false;
		GameObject gameObject;
	} g_clipBoard;

	DebugMode debugMode = DebugMode::NONE;
	int g_selectionIndex;



	void init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Backend::getWindowPointer(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		Gizmo::init();
		g_selectionIndex = -1;
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

		// deleting game objects
		if (Input::keyPressed(SIN_KEY_DELETE) && g_selectionIndex != -1) {
			Game::scene.gameObjects.erase(Game::scene.gameObjects.begin() + g_selectionIndex);
			g_selectionIndex = -1;
		}

		// adding game objects
		if (Input::keyPressed(SIN_KEY_INSERT)) {
			GameObject newObj("cube");
			newObj.transform.setPosition(Camera::m_position + Camera::_forward * 3.0f);
			Game::scene.add(newObj);
		}

		if (Input::keyDown(SIN_KEY_LEFT_CONTROL) && Input::keyPressed(SIN_KEY_C)) {
			if (g_selectionIndex != -1) {
				g_clipBoard.gameObject = Game::scene.gameObjects[g_selectionIndex];
				g_clipBoard.copied = true;
			}
		}

		if (Input::keyDown(SIN_KEY_LEFT_CONTROL) && Input::keyPressed(SIN_KEY_V) && g_clipBoard.copied) {
			Game::scene.add(g_clipBoard.gameObject);
		}

		if (g_selectionIndex != -1)
		{
			Gizmo::update(Game::scene.gameObjects[g_selectionIndex].transform);
		}
	}
};

void Editor::draw() {
    OpenGLBackend::update();
    static GBuffer& gbuffer = OpenGLBackend::gbuffer;
    gbuffer.bind();

    // Deferred rendering
    if (OpenGLRenderer::renderMode == RenderMode::DEFERRED) {
        // Geometry pass
        OpenGLRenderer::beginFrame();
        OpenGLRenderer::bindVAO();
        Game::render();
        OpenGLRenderer::unbindVAO();

        // Lighting pass
        gbuffer.draw();
        OpenGLRenderer::bindVAO();
        for (const auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        OpenGLRenderer::unbindVAO();
    }
    // Forward rendering
    else if (OpenGLRenderer::renderMode == RenderMode::FORWARD) {
        OpenGLRenderer::beginFrame();
        OpenGLRenderer::bindVAO();
        Game::render();
        for (const auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        OpenGLRenderer::unbindVAO();
    }

    if (g_selectionIndex != -1) Gizmo::draw();
    if (debugMode == DebugMode::AABB) {
        OpenGLRenderer::debugAABBs();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Begin dockspace
    static bool dockspaceOpen = true;
    static bool optFullscreen = true;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen) {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Dockspace", &dockspaceOpen, windowFlags);
    ImGui::PopStyleVar(2);

    // Create the dockspace
    ImGuiID dockspaceID = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

    // Add a menu bar (optional)
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                // Handle exit
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Render game window
    ImGui::Begin("GameWindow");
    {
        ImVec2 contentSize = ImGui::GetContentRegionAvail();
        if (contentSize.x != Backend::getWinWidth() || contentSize.y != Backend::getWinHeight()) {
            Backend::frameBufferSizeCallback(Backend::getWindowPointer(), (int)contentSize.x, (int)contentSize.y);
        }
        ImGui::Image((ImTextureID)gbuffer.screen, contentSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();

    ImGui::End(); // End dockspace window

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Multi-viewport handling (optional, for ViewportsEnable)
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

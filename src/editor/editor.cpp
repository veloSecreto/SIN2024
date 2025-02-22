#include "editor.h"
#include "../input/input.h"
#include "../game/_camera.h"
#include "../game/game.h"
#include "../api/opengl/gl_renderer.h"
#include "../api/opengl/gl_backend.h"
#include "gizmo.hpp"
#include "../physics/physics.h"
#include "../file/file_system.h"
#include "../api/opengl/render_passes/render_passes.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


void SetEditorTheme();
void GizmoAndOtherStuffs();
void EditorUserInterfacePass();

glm::vec3 mouseRayDirection;

namespace Editor {

	struct ClipBoard {
		bool copied = false;
		GameObject gameObject;
	} g_clipBoard;

	DebugMode debugMode = DebugMode::NONE;
	int g_selectionIndex;
	int g_hoveredIndex;
	bool sceneViewportHasfocus;
	ImVec2 sceneViewport;
	
	
	
	void init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF((ROOT_DIR + "res/fonts/Merriweather Sans/regular.ttf").c_str(), 16.0f);
		SetEditorTheme();
		ImGui_ImplGlfw_InitForOpenGL(Backend::getWindowPointer(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		Gizmo::init();
		g_hoveredIndex = g_selectionIndex = -1;
		std::cout << "Editor is initialized" << std::endl;
	}	
};



void Editor::update() {
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

	// Hover
	Ray mouseRay = { Camera::m_position, mouseRayDirection };
	if (!Gizmo::hasHover())
	{
		float nearestDistance = std::numeric_limits<float>::max();
		int closestObjectIndex = -1;

		for (unsigned int i = 0; i < Game::scene.gameObjects.size(); ++i) {
			AABB& aabb = Game::scene.gameObjects[i].aabb;
			float tMin;

			bool hit = Physics::intersection(mouseRay, aabb, tMin);
			if (hit && tMin < nearestDistance) {
				nearestDistance = tMin;
				closestObjectIndex = i;
			}
		}
		
		g_hoveredIndex = closestObjectIndex;
	}

	if (Input::mouseButtonPressed(SIN_MOUSE_BUTTON_LEFT) && !Gizmo::hasHover())
	{
		g_selectionIndex = g_hoveredIndex;
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
	static int i = 0;
	if (Input::keyPressed(SIN_KEY_INSERT)) {
		GameObject newObj("cube");
		newObj.name = "Cube" + std::to_string(i++);
		newObj.transform.setPosition(Camera::m_position + Camera::_forward * 3.0f);
		Game::scene.add(newObj);
	}

	if (Input::keyDown(SIN_KEY_LEFT_CONTROL) && Input::keyPressed(SIN_KEY_C)) {
		if (g_selectionIndex != -1) {
			g_clipBoard.gameObject = Game::scene.gameObjects[g_selectionIndex];
			g_clipBoard.gameObject.name += std::to_string(i);
			g_clipBoard.copied = true;
		}
	}

	if (Input::keyDown(SIN_KEY_LEFT_CONTROL) && Input::keyPressed(SIN_KEY_V) && g_clipBoard.copied) {
		Game::scene.add(g_clipBoard.gameObject);
	}

	if (g_selectionIndex != -1)
	{
		Gizmo::update(Game::scene.gameObjects[g_selectionIndex].transform, mouseRayDirection);
	}
}

void Editor::draw() {
	OpenGLBackend::update();
	ShadowMapPass();
	RenderPass();
	PostProcessingPass();
	GizmoAndOtherStuffs();
	EditorUserInterfacePass();
}


void SetEditorTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Backgrounds
    colors[ImGuiCol_WindowBg]            = ImVec4(0.08f, 0.08f, 0.08f, 1.00f); // Very dark gray
    colors[ImGuiCol_ChildBg]             = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Slightly lighter
    colors[ImGuiCol_PopupBg]             = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Popup menus

    // Borders
    colors[ImGuiCol_Border]              = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Dark border
    colors[ImGuiCol_BorderShadow]        = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // No shadow

    // Text
    colors[ImGuiCol_Text]                = ImVec4(0.90f, 0.90f, 0.90f, 1.00f); // Light gray text
    colors[ImGuiCol_TextDisabled]        = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Muted gray for disabled text

    // Headers
    colors[ImGuiCol_Header]              = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Darker header
    colors[ImGuiCol_HeaderHovered]       = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Slightly lighter hover
    colors[ImGuiCol_HeaderActive]        = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Active header

    // Buttons
    colors[ImGuiCol_Button]              = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Dark button
    colors[ImGuiCol_ButtonHovered]       = ImVec4(0.26f, 0.26f, 0.26f, 1.00f); // Button hover
    colors[ImGuiCol_ButtonActive]        = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); // Active button state

    // Frame (Input boxes, sliders)
    colors[ImGuiCol_FrameBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f); // Dark input boxes
    colors[ImGuiCol_FrameBgHovered]      = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Hover effect
    colors[ImGuiCol_FrameBgActive]       = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Active state

    // Tabs
    colors[ImGuiCol_Tab]                 = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Dark tab
    colors[ImGuiCol_TabHovered]          = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Hover effect on tab
    colors[ImGuiCol_TabActive]           = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Active tab
    colors[ImGuiCol_TabUnfocused]        = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Unfocused tab
    colors[ImGuiCol_TabUnfocusedActive]  = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Unfocused active tab

    // Titles
    colors[ImGuiCol_TitleBg]             = ImVec4(0.08f, 0.08f, 0.08f, 1.00f); // Title bar background
    colors[ImGuiCol_TitleBgActive]       = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Active title
    colors[ImGuiCol_TitleBgCollapsed]    = ImVec4(0.08f, 0.08f, 0.08f, 0.75f); // Collapsed state

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]         = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Dark scrollbar background
    colors[ImGuiCol_ScrollbarGrab]       = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Scrollbar grab color
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Hover effect on scrollbar
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f); // Active state of scrollbar

    // Resize Grip
    colors[ImGuiCol_ResizeGrip]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); // Resize grip
    colors[ImGuiCol_ResizeGripHovered]   = ImVec4(0.24f, 0.24f, 0.24f, 1.00f); // Hover effect
    colors[ImGuiCol_ResizeGripActive]    = ImVec4(0.28f, 0.28f, 0.28f, 1.00f); // Active state

    // Misc
    colors[ImGuiCol_CheckMark]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Muted gray checkmark
    colors[ImGuiCol_SliderGrab]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Slider grab
    colors[ImGuiCol_SliderGrabActive]    = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Active slider grab
    colors[ImGuiCol_Separator]           = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Separator line
    colors[ImGuiCol_SeparatorHovered]    = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // Hover effect on separator
    colors[ImGuiCol_SeparatorActive]     = ImVec4(0.26f, 0.26f, 0.26f, 1.00f); // Active separator

    // Style tweaks
    style.FrameRounding = 4.0f;  // Rounded edges
    style.WindowRounding = 6.0f; // Slightly rounded windows
    style.GrabRounding = 4.0f;   // Rounded sliders/buttons
}

void GizmoAndOtherStuffs() {
	OpenGLBackend::gbuffer.bind();
	if (Editor::g_selectionIndex != -1) { 
		Gizmo::draw(glm::vec2(Editor::sceneViewport.x, Editor::sceneViewport.y));
		// Gizmo::draw(glm::vec2(static_cast<float>(Backend::getWinWidth()), static_cast<float>(Backend::getWinHeight())));
		OpenGLRenderer::debugAABB(Game::scene.gameObjects[Editor::g_selectionIndex].aabb, glm::vec3(1, 0.2, 0));
	}
	if (Editor::g_hoveredIndex != -1 && Editor::g_hoveredIndex != Editor::g_selectionIndex) {
		OpenGLRenderer::debugAABB(Game::scene.gameObjects[Editor::g_hoveredIndex].aabb, glm::vec3(0.65f));
	}
	if (Editor::debugMode == DebugMode::AABB) {
		OpenGLRenderer::debugAABBs();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void EditorUserInterfacePass() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

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
	if (ImGui::Begin("Dockspace", &dockspaceOpen, windowFlags)) {
		ImGui::PopStyleVar(2);

		ImGuiID dockspaceID = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit")) {
					Backend::forceCloseWindow();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Scene Viewport");
		{
			ImVec2 contentSize = ImGui::GetContentRegionAvail();
			Editor::sceneViewportHasfocus = ImGui::IsWindowFocused();

			ImVec2 mousePos = ImGui::GetMousePos();
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 mousePosInWindow = { mousePos.x - windowPos.x, mousePos.y - windowPos.y };
			float ndcX = (2.0f * mousePosInWindow.x / windowSize.x) - 1.0f;
			float ndcY = 1.0f - (2.0f * mousePosInWindow.y / windowSize.y);
			float ndcZ = 1.0f;
			glm::vec3 ray_nds = glm::vec3(ndcX, ndcY, ndcZ);
			glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
			glm::vec4 ray_eye = glm::inverse(Camera::m_proj) * ray_clip;
			ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
			mouseRayDirection = glm::vec3(glm::inverse(Camera::m_view) * ray_eye);
			mouseRayDirection = glm::normalize(mouseRayDirection);

			/*
			glm::vec4 ndc(ndcX, ndcY, ndcZ, 1.0f);
			glm::vec4 worldPos = glm::inverse(Camera::m_proj * Camera::m_view) * ndc;
			worldPos /= worldPos.w;
			mouseRayDirection = glm::normalize(glm::vec3(worldPos));
			*/

			if (contentSize.x > 0 && contentSize.y > 0 &&
				(contentSize.x != Editor::sceneViewport.x || contentSize.y != Editor::sceneViewport.y)) {
				OpenGLRenderer::onResize(contentSize.x, contentSize.y);
				Editor::sceneViewport = contentSize;
			}

			ImGui::Image((ImTextureID)OpenGLBackend::gbuffer.screen, contentSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();

		ImGui::Begin("Scene Hierarchy");
		{
			ImGui::Spacing();
			for (int i = 0; i < Game::scene.gameObjects.size(); i++) {
				if (ImGui::Selectable((Game::scene.gameObjects[i].name).c_str(), Editor::g_selectionIndex == i)) {
					Editor::g_selectionIndex = i;
				}
			}
		}
        ImGui::End();

		ImGui::Begin("Properties");
		{
			if (Editor::g_selectionIndex != -1) {
				GameObject& gameObject = Game::scene.gameObjects[Editor::g_selectionIndex];
				
				ImGui::Text("Game Object Properties");
				ImGui::Separator();
				
				// Name
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strncpy(buffer, gameObject.name.c_str(), sizeof(buffer) - 1);
				if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
					if (buffer != "") gameObject.name = buffer;
				}
				
				// Model Name
				memset(buffer, 0, sizeof(buffer));
				strncpy(buffer, gameObject._modelName.c_str(), sizeof(buffer) - 1);
				if (ImGui::InputText("Model", buffer, sizeof(buffer))) {
					if (AssetManager::g_models.contains(buffer)) {
						gameObject._modelName = buffer;
						gameObject.model = AssetManager::getModelByName(gameObject._modelName);
					}
				}
				
				// Transform - Position
				ImGui::Text("Transform");
				glm::vec3 position = gameObject.transform.getPosition();
				glm::vec3 rotation = gameObject.transform.getRotation();
				glm::vec3 scale = gameObject.transform.getScale();

				// Modify them via ImGui
				if (ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f)) {
					gameObject.transform.setPosition(position);
				}
				if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f)) {
					gameObject.transform.setRotation(rotation);
				}
				if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f, 0.01f, 100.0f)) {
					gameObject.transform.setScale(scale);
				}
				
				// AABB (For Debugging)
				ImGui::Text("AABB");
				ImGui::Text("Min: (%.2f, %.2f, %.2f)", gameObject.aabb.min.x, gameObject.aabb.min.y, gameObject.aabb.min.z);
				ImGui::Text("Max: (%.2f, %.2f, %.2f)", gameObject.aabb.max.x, gameObject.aabb.max.y, gameObject.aabb.max.z);

				ImGui::Separator();
				auto fps = std::to_string(Clock::fps);
				ImGui::Text(fps.c_str());
			}
			else {
				ImGui::Text("Select a Game Object to View Properties");
			}
		}
		ImGui::End();
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupCurrentContext);
	}
	
	/*
	static Shader* shader = OpenGLRenderer::g_shaders["screen"];
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer.screen);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(gbuffer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	*/
}

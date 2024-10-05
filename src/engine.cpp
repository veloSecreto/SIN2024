#include "engine.h"

namespace Engine {

    // Initializes the BackEnd and all other subsytems along with modifications
    // ------------------------------------------------------------------------
    void init() {
        Backend::init();
        AssetManager::loadAll();
        OpenGLRenderer::uploadBuffersToGPU();

        // Subsystems
        Input::init();
    }

    // Starts running the main Engine itself
    // -------------------------------------
    void run() {
        while (Backend::windowIsOpen()) {
            Clock::update();

            OpenGLRenderer::beginFrame();
            Backend::beginFrame();
            Input::update();

            if (Input::keyPressed(SIN_KEY_INSERT)) {
                OpenGLRenderer::hotLoadShaders();
            }

            if (Backend::getAPI() == API::OPENGL) {
                OpenGLRenderer::render();
            }
            else if (Backend::getAPI() == API::VULKAN) {
                // Render for VULKAN System, not made yet
            }

            Backend::endFrame();
        }
    }
};
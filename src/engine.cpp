#include "engine.h"
#include "backend/backend.h"
#include "clock.hpp"
#include "api/opengl/gl_renderer.h"
#include "api/opengl/gl_backend.h"
#include "core/asset_manager.h"
#include "input/input.h"
#include "game/game.h"

namespace Engine {

    // Initializes the BackEnd and all other subsytems along with modifications
    // ------------------------------------------------------------------------
    void init() {
        Backend::init();
        Game::start();

        // buffer pass
        OpenGLRenderer::uploadBuffersToGPU();
        OpenGLBackend::createSSBOs();
        OpenGLBackend::uploadSSBOsToGPU();
        
        // final injection
        Backend::show();
        // subsystems
        Input::init();
        Input::disableCursor();
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

            // if (Backend::getAPI() == API::OPENGL) {
            //     OpenGLRenderer::render();
            // }
            // else if (Backend::getAPI() == API::VULKAN) {
            //     // Render for VULKAN System, not made yet
            // }

            OpenGLRenderer::bindVAO();
            Game::render();
            OpenGLRenderer::unbindVAO();

            Backend::endFrame();
        }
    }
};
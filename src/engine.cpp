#include "engine.h"
<<<<<<< HEAD
#include "api/opengl/gl_renderer.h"
#include "api/opengl/gl_backend.h"
#include "core/asset_manager.h"
=======
#include "backend/backend.h"
#include "clock.hpp"
#include "api/opengl/gl_renderer.h"
#include "api/opengl/gl_backend.h"
#include "core/asset_manager.h"
#include "input/input.h"
#include "game/game.h"
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

namespace Engine {

    // Initializes the BackEnd and all other subsytems along with modifications
    // ------------------------------------------------------------------------
    void init() {
        Backend::init();
<<<<<<< HEAD
        AssetManager::loadAll();
        OpenGLRenderer::uploadBuffersToGPU();

        // Subsystems
        Input::init();
=======

        // Subsystems
        Input::init();
        Game::init();
        Game::start();
    
        // buffer pass
        OpenGLRenderer::uploadBuffersToGPU();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
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

<<<<<<< HEAD
            // todo: implement game and render with that
=======
            OpenGLRenderer::bindVAO();
            Game::render();
            OpenGLRenderer::unbindVAO();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

            Backend::endFrame();
        }
    }
};
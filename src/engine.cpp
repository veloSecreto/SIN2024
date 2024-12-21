#include "engine.h"
#include "backend/backend.h"
#include "clock.hpp"
#include "api/opengl/gl_renderer.h"
#include "api/opengl/gl_backend.h"
#include "core/asset_manager.h"
#include "input/input.h"
#include "game/game.h"
#include "editor/editor.h"

namespace Engine {
    Mode mode = Mode::Editing;

    // Initializes the BackEnd and all other subsytems along with modifications
    // ------------------------------------------------------------------------
    void init() {
        Backend::init();
        Game::init();
        Editor::init();
        
        OpenGLRenderer::uploadBuffersToGPU();
        OpenGLBackend::createSSBOs();
        OpenGLBackend::uploadSSBOsToGPU();
        OpenGLBackend::configureFBOs();
        
        Backend::show();
        Input::init();

        std::cout << "\nPreparation has been completed\nEngine is ready to run\n\n";
    }

    // Starts running the main Engine itself
    // -------------------------------------
    void run() {
        while (Backend::windowIsOpen()) {
            Clock::update();
            Backend::beginFrame();
            Input::update();
            Backend::setWindowTitle("Unloved  | FPS: " + std::to_string(Clock::fps));

            if (Input::keyPressed(SIN_KEY_H)) {
                OpenGLRenderer::hotLoadShaders();
            }
            if (Input::keyPressed(SIN_KEY_P)) {
                mode = mode == Mode::Editing ? Mode::Playing : Mode::Editing;
            }

            if (mode == Mode::Playing)
            {
                Game::update();
                OpenGLRenderer::renderFrame();
            }
            else
            {
                OpenGLRenderer::renderFrame();
                Editor::update();
            }

            Backend::endFrame();
        }
        Backend::kill();
    }
};
#include "engine.h"
#include "backend/backend.h"
#include "clock.hpp"
#include "api/opengl/gl_renderer.h"
#include "api/opengl/gl_backend.h"
#include "core/asset_manager.h"
#include "input/input.h"
#include "game/game.h"
#include "editor/editor.h"
#include "file/file_system.h"

namespace Engine {
    Mode mode = Mode::Playing;

    // Initializes the BackEnd and all other subsytems along with modifications
    // ------------------------------------------------------------------------
    void init() {
        Backend::init();
        FileSystem::init();
        Game::init();
        Editor::init();
        
        OpenGLBackend::upload();
        OpenGLRenderer::uploadBuffersToGPU();
        
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

            if (Input::keyPressed(SIN_KEY_H)) {
                OpenGLRenderer::hotLoadShaders();
            }
            if (Input::keyPressed(SIN_KEY_P)) {
                if (mode == Mode::Editing) {
                    mode = Mode::Playing;
                }
                else {
                    mode = Mode::Editing;
                }
            }

            if (mode == Mode::Playing)
            {
                Game::update();
                OpenGLRenderer::renderFrame();
            }
            else
            {
                Editor::update();
                Editor::draw();
            }

            Backend::endFrame();
        }
    }
};

void Engine::clean() {
    Backend::kill();
}
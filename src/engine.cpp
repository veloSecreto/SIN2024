#include "engine.h"

namespace Engine {
    void init() {
        Backend::init();
        Input::init();
    }

    void run() {
        while (Backend::windowIsOpen()) {
            Backend::beginFrame();
            Input::update();

            OpenGLRenderer::render();

            Backend::endFrame();
        }
    }
};
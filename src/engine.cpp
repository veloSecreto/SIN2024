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
#include "game_object.h"
#include "../api/opengl/gl_renderer.h"
#include "../physics/physics.h"

GameObject::GameObject(const std::string& modelName) {
    _modelName = modelName;
    model = AssetManager::getModelByName(modelName);
    // From local to World space coordinates
    aabb = Physics::calculateOBB(model.localAABB, transform);
}

void GameObject::update() {
    if (transform.dirty) {
        aabb = Physics::calculateOBB(model.localAABB, transform);
    }
}
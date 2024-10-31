#include "game.h"
#include "../core/asset_manager.h"

std::unordered_map<std::string, Scene> Game::scenes;
bool Game::loaded = false;
GameObject Game::object, Game::object2;

void Game::createScene(const std::string& name) {
    scenes[name] = Scene();
}

void Game::start() {
    createScene("main");
    AssetManager::loadAll();

    // note: for testing only
    object = GameObject("mushroom", "default");
    std::cout << "Mushroom has " << object.model.getMeshes().size() << " meshes" << std::endl;
    object2 = GameObject("mushroom", "default");
    std::cout << "mushroom has " << object2.model.getMeshes().size() << " meshes" << std::endl;
    scenes["main"].add(object);
    scenes["main"].add(object2);
    loaded = true;
}

void Game::render() {
    // scenes["main"].render();
    Camera::update();
    Shader shader = OpenGLRenderer::getDefaultShader();
    Transform trans1, trans2;
    trans1.position = glm::vec3(2.0f, 0.0f, 0.0f);
    trans2.position = glm::vec3(-4.0f, 0.0f, 0.0f);
    shader.use();
    shader.setMat4x4("m_proj", Camera::m_proj);
    shader.setMat4x4("m_view", Camera::m_view);

    shader.use();
    shader.setMat4x4("m_model", trans1.to_mat4());
    object.model.render(shader);
    shader.use();
    shader.setMat4x4("m_model", trans2.to_mat4());
    object2.model.render(shader);
}
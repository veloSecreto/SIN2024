#include "game.h"
#include "../core/asset_manager.h"

std::unordered_map<std::string, Scene> Game::scenes;
bool Game::loaded = false;

void Game::init() {
    createScene("main");
}

void Game::createScene(const std::string& name) {
    scenes[name] = Scene();
}

void Game::start() {
    AssetManager::loadAll();

    // note: for testing only
    GameObject object("mushroom", "default");
    scenes["main"].add(object);
    loaded = true;
}

void Game::render() {
    scenes["main"].render();
}
#include "file_system.h"
#include "../defines.h"
#include "../game/game.h"
#include <fstream>

namespace FileSystem {
	namespace Repository {
		nlohmann::json sceneData;

		void init() {
			std::ifstream file(ROOT_DIR + "res/data/scene.json");

			if (!file.is_open()) {
				std::cerr << "Failed to load scene data: Could not open file at "
					<< "SIN2024/res/data/scene.json" << std::endl;
				return;
			}

			try {
				file >> sceneData;
				std::cout << "Scene data loaded successfully from "
					<< "SIN2024/res/data/scene.json" << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "Failed to load scene data: " << e.what() << std::endl;
			}

			file.close();
		}

		nlohmann::json& getSceneData() {
			return sceneData;
		}

		void saveSceneData() {
			sceneData["Game Objects"] = nlohmann::json::array();
			sceneData["Lights"] = nlohmann::json::array();

			for (unsigned int i = 0; i < Game::scene.gameObjects.size(); i++) {
				GameObject& obj = Game::scene.gameObjects[i];
				const auto& pos = obj.transform.getPosition();
				const auto& rot = obj.transform.getRotation();
				const auto& scale = obj.transform.getScale();
				sceneData["Game Objects"][i]["Model Name"] = obj._modelName;
				sceneData["Game Objects"][i]["Position"] = { pos.x, pos.y, pos.z };
				sceneData["Game Objects"][i]["Rotation"] = { rot.x, rot.y, rot.z };
				sceneData["Game Objects"][i]["Scale"] = { scale.x, scale.y, scale.z };
			}

			for (unsigned int i = 0; i < Game::scene.lights.size(); i++) {
				const Light& light = Game::scene.lights[i];
				sceneData["Lights"][i]["Position"] = { light.position.x, light.position.y, light.position.z };
				sceneData["Lights"][i]["Color"] = { light.color.x, light.color.y, light.color.z };
				sceneData["Lights"][i]["Strength"] = light.strength;
				sceneData["Lights"][i]["Radius"] = light.radius;
			}

			std::ofstream file(ROOT_DIR + "res/data/scene.json");
			if (file.is_open()) {
				file << sceneData.dump(4);
				file.close();
				std::cout << "Scene data saved successfully" << std::endl;
			}
			else {
				std::cerr << "Failed to load file at path: '../../res/data/scene.json' for saving scene data" << std::endl;
			}
		}
	}

	void init() {
		Repository::init();
	}
}
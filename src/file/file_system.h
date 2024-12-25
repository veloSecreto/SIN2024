#pragma once

#include <json/json.hpp>

namespace FileSystem {
	namespace Repository {
		void init();
		nlohmann::json& getSceneData();
		void saveSceneData();
	}

	void init();
}
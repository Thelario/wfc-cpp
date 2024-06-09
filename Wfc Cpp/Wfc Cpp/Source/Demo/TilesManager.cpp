#pragma warning(disable : 26812)

#include "TilesManager.h"

#include <iostream>
#include <fstream>

#include "../Engine/Engine.h"
#include "../Engine/LoggerManager.h"
#include "../Engine/json.hpp"

using namespace Satellite;
using json = nlohmann::json;

namespace Demo
{
	TileInfo::TileInfo(TileSideInfo left_side, TileSideInfo right_side, TileSideInfo upper_side, TileSideInfo down_side, const std::string& texture_id, int id)
		: left_side(left_side), right_side(right_side), upper_side(upper_side), down_side(down_side), texture_id(texture_id), id(id)
	{ }

	TilesManager* TilesManager::Instance()
	{
		static TilesManager* instance = new TilesManager();
		return instance;
	}

	void TilesManager::Start()
	{
		LoadTilesInfo();

		CreateReferenceTilemap();
	}

	void TilesManager::LoadTilesInfo()
	{
		// Load all the tile's info

		const std::string asset_id = "tilemap";

		const std::string& config_file_name = "./Config/tiles_info_config.json";

		std::ifstream file;

		file.open(config_file_name);

		if (file.fail() == true) {
			LoggerManager::Error("Failed to open file: " + config_file_name);
			return;
		}

		json json_data = json::parse(file);

		int i = 0;
		for (const auto& tile_info : json_data["tiles_info"])
		{
			tiles_info[i] = new TileInfo(tile_info["left_side"], tile_info["right_side"], tile_info["upper_side"], tile_info["down_side"], asset_id, tile_info["id"]);
			i++;
		}
	}

	void TilesManager::CreateReferenceTilemap()
	{
		// Creating the tilemap to show the possible tiles that might appear

		for (int u = 0; u < 16; u++)
		{
			TileInfo* tile_info = tiles_info[u];

			int x = (u % 4) * 28 + 40;
			int y = (int)(u / 4) * 28 + 40;

			Engine::Instance()->CreateObject(new GameObject(glm::vec2(x, y),
				glm::vec2(1.5), 0, tile_info->texture_id, 16, 16, false, tile_info->id));
		}
	}

	TileInfo** TilesManager::GetTilesInfoArray() {
		return tiles_info;
	}

	int TilesManager::GetTilesInfoArraySize() { return SIZE; }
}
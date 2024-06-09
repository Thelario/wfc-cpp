#pragma once

#include <string>
#include <vector>

#include "Tile.h"

namespace Demo
{
	enum TileSideInfo {
		WATER,  // 0
		GRASS, // 1
		BEACH_LEFT, // 2
		BEACH_RIGHT, // 3
		BEACH_UP, // 4
		BEACH_DOWN // 5
	};

	// A tile can be connected to another if the side connecting is of the
	// same type as the side of the other tile.

	class TileInfo
	{
		public:
			std::string texture_id;
			int id;

			TileSideInfo left_side;
			TileSideInfo right_side;
			TileSideInfo upper_side;
			TileSideInfo down_side;

		public:
			TileInfo(TileSideInfo left_side, TileSideInfo right_side, TileSideInfo upper_side, TileSideInfo down_side, const std::string& texture_id, int id);
	};

	class TilesManager
	{
		private:
			static const int SIZE = 16;
			TileInfo *tiles_info[SIZE];

			void LoadTilesInfo();
			void CreateReferenceTilemap();

		public:
			static TilesManager* Instance();
			
			void Start();

			TileInfo** GetTilesInfoArray();
			int GetTilesInfoArraySize();
			std::vector<TileInfo*> GetPossibleTiles(Tile* tile, Tile* neighbor);
	};
}
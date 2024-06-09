#pragma once

#include "Tile.h"

namespace Demo
{
	class Grid
	{
		private:
			static const int max_width = 10;
			static const int max_height = 8;
			static const int size = 27;
			static const int x_offset = 192;
			static const int y_offset = 40;
			
			Tile* grid[max_width][max_height];

		public:
			static Grid* Instance();

			void CreateGrid();
			void PropagateResult(int x, int y);
			std::vector<Tile*> FindNeighbors(int x, int y);
	};
}
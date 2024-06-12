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

			bool collapse_grid = false;
			double time_between_collapses = 0.1;
			double time_between_collapses_counter;
			
			Tile* grid[max_width][max_height];

		public:
			static Grid* Instance();
			~Grid();

			void Update();

			void CreateGrid();
			void ResetGrid();
			void SolveGrid();

			Tile* FindCellWithLowestEntropy();
			void PropagateResult(int x, int y);
			std::vector<Tile*> FindNeighbors(int x, int y);
	};
}
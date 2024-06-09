#include "Grid.h"

#include "../Engine/Engine.h"
#include "../Engine/LoggerManager.h"

#include "Tile.h"
#include <stack>

namespace Demo
{
	Grid* Grid::Instance()
	{
		static Grid* instance = new Grid();
		return instance;
	}

	void Grid::CreateGrid()
	{
		for (int x = 0; x < max_width; x++)
		{
			for (int y = 0; y < max_height; y++)
			{
				int real_x = x_offset + x * size;
				int real_y = y_offset + y * size;

				Tile* tile = new Tile(glm::vec2(real_x, real_y), glm::vec2(2), 0, "empty-tile", 16, 16, false, 0, true, 0,
					SDL_Color({ 255, 255, 255, 255 }), true, true, false, glm::vec2(0), glm::vec2(0), Satellite::ColliderTag::NONE, x, y);
				Engine::Instance()->CreateObject(tile);
				grid[x][y] = tile;
			}
		}
	}

	void Grid::PropagateResult(int x, int y)
	{
		// We add the tile we just collapsed into a stack

		std::stack<Tile*> stack;
		stack.push(grid[x][y]);
		
		// We loop while there are pending tiles in the stack
		
		while (!stack.empty())
		{
			// We pop a pending grid tile from the stack

			Tile* tile = stack.top();
			stack.pop();

			// We iterate over each adjacent tile to this one (find the neighbors and iterate over them).
			
			std::vector<Tile*> neighbors = FindNeighbors(x, y);
			
			// For each neighbor:
			
			for (Tile* neighbor : neighbors)
			{
				std::vector<TileInfo*> neighbor_potential_tiles = neighbor->GetPotentialTilesCopy();

				// We need to find the tiles our "tile" can be connected to

				std::vector<TileInfo*> tile_possible_neighbors = TilesManager::Instance()->GetPossibleTiles(tile, neighbor);

				// If there aren't potential tiles, we continue.

				if (tile_possible_neighbors.size() == 0) {
					continue;
				}

				bool neighbor_modified = false;
				std::vector<TileInfo*> new_neighbor_potential_tiles;

				// For each potential tile:

				for (TileInfo* tile_info : neighbor->potential_tiles)
				{
					// If the tile is not present in the list of possible neighbors, then we remove it.


				}

				if (!neighbor_modified || grid[x][y]->collapsed) {
					continue;
				}

				neighbor->potential_tiles = new_neighbor_potential_tiles;
				stack.push(neighbor);
			}
		}
	}

	std::vector<Tile*> Grid::FindNeighbors(int x, int y)
	{
		std::vector<Tile*> neighbors;

		if (x == 0 && y == 0) // Left-top corner
		{
			neighbors.push_back(grid[1][0]);
			neighbors.push_back(grid[0][1]);
		}
		else if (x == max_width - 1 && y == 0) // Left-down corner
		{
			neighbors.push_back(grid[x][1]);
			neighbors.push_back(grid[x-1][0]);
		}
		else if (x == 0 && y == max_height - 1) // Right-top corner
		{
			neighbors.push_back(grid[0][y-1]);
			neighbors.push_back(grid[1][y]);
		}
		else if (x == max_width - 1 && y == max_height - 1) // Right-down corner
		{
			neighbors.push_back(grid[x-1][y]);
			neighbors.push_back(grid[x][y-1]);
		}
		else if (x == 0) // Upper side
		{
			neighbors.push_back(grid[x][y-1]);
			neighbors.push_back(grid[x][y+1]);
			neighbors.push_back(grid[1][y]);
		}
		else if (x == max_width - 1) // Lower side
		{
			neighbors.push_back(grid[x][y-1]);
			neighbors.push_back(grid[x][y+1]);
			neighbors.push_back(grid[x-1][y]);
		}
		else if (y == 0) // Left side
		{
			neighbors.push_back(grid[x-1][y]);
			neighbors.push_back(grid[x+1][y]);
			neighbors.push_back(grid[x][1]);
		}
		else if (y == max_height - 1) // Right side
		{
			neighbors.push_back(grid[x-1][y]);
			neighbors.push_back(grid[x+1][y]);
			neighbors.push_back(grid[x][y-1]);
		}
		else // Surrounded by tiles
		{
			neighbors.push_back(grid[x][y+1]);
			neighbors.push_back(grid[x][y-1]);
			neighbors.push_back(grid[x+1][y]);
			neighbors.push_back(grid[x-1][y]);
		}

		return neighbors;
	}
}
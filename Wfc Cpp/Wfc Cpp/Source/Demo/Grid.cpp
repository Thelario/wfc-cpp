#include "Grid.h"

#include "../Engine/Engine.h"
#include "../Engine/LoggerManager.h"
#include "../Engine/InputManager.h"

#include "Tile.h"
#include <stack>

using namespace Satellite;

namespace Demo
{
	Grid* Grid::Instance()
	{
		static Grid* instance = new Grid();
		return instance;
	}

	Grid::~Grid()
	{
		for (int x = 0; x < max_width; x++)
		{
			for (int y = 0; y < max_height; y++)
			{
				Engine::Instance()->DestroyObject(grid[x][y]);
			}
		}
	}

	void Grid::Update()
	{
		if (InputManager::GetKeyUp(KeyCode::SPACE)) {
			collapse_grid = true;
			time_between_collapses_counter = time_between_collapses;
		}
		else if (InputManager::GetKeyUp(KeyCode::ESCAPE)) {
			ResetGrid();
			collapse_grid = false;
		}

		if (collapse_grid == false) {
			return;
		}

		time_between_collapses_counter -= Engine::Instance()->GetDeltaTime();
		if (time_between_collapses_counter <= 0) {
			SolveGrid();
		}
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

	void Grid::ResetGrid()
	{
		for (int x = 0; x < max_width; x++)
		{
			for (int y = 0; y < max_height; y++)
			{
				int real_x = x_offset + x * size;
				int real_y = y_offset + y * size;

				Engine::Instance()->DestroyObject(grid[x][y]);

				Tile* tile = new Tile(glm::vec2(real_x, real_y), glm::vec2(2), 0, "empty-tile", 16, 16, false, 0, true, 0,
					SDL_Color({ 255, 255, 255, 255 }), true, true, false, glm::vec2(0), glm::vec2(0), Satellite::ColliderTag::NONE, x, y);
				Engine::Instance()->CreateObject(tile);
				grid[x][y] = tile;
			}
		}
	}

	void Grid::SolveGrid()
	{
		Tile* tile = FindCellWithLowestEntropy();
		if (tile == nullptr) {
			return;
		}

		tile->Collapse();

		PropagateResult(tile->x, tile->y);

		time_between_collapses_counter = time_between_collapses;
	}

	Tile* Grid::FindCellWithLowestEntropy()
	{
		int entropy = 99999;

		std::vector<Tile*> lowest_entropy_tiles;

		for (int x = 0; x < max_width; x++)
		{
			for (int y = 0; y < max_height; y++)
			{
				if (grid[x][y]->collapsed)
					continue;

				if (grid[x][y]->potential_tiles.size() == entropy) {
					lowest_entropy_tiles.push_back(grid[x][y]);
				}
				else if (grid[x][y]->potential_tiles.size() < entropy) {
					lowest_entropy_tiles.clear();
					lowest_entropy_tiles.push_back(grid[x][y]);
					entropy = grid[x][y]->potential_tiles.size();
				}
			}
		}

		if (lowest_entropy_tiles.size() == 0) {
			collapse_grid = false;
			return nullptr;
		}

		int id = Engine::Instance()->GetRandom()->GenerateRandomInteger(0, lowest_entropy_tiles.size() - 1);
		return lowest_entropy_tiles.at(id);
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
			
			std::vector<Tile*> neighbors = FindNeighbors(tile->x, tile->y);
			
			// For each neighbor:
			
			for (Tile* neighbor : neighbors)
			{
				std::vector<TileInfo*> neighbor_potential_tiles = neighbor->GetPotentialTilesCopy();

				// We need to find the tiles our "tile" can be connected to

				std::vector<TileInfo*> tile_possible_neighbors = TilesManager::Instance()->GetPossibleTiles(tile, neighbor);

				// If there aren't potential tiles, we continue.

				if (neighbor_potential_tiles.size() == 0) {
					continue;
				}

				bool neighbor_modified = false;
				std::vector<TileInfo*> new_neighbor_potential_tiles;

				// For each potential tile:

				for (TileInfo* tile_info : neighbor_potential_tiles)
				{
					// If the tile is not present in the list of possible neighbors, then we remove it.

					if (std::find(tile_possible_neighbors.begin(), tile_possible_neighbors.end(), tile_info) != tile_possible_neighbors.end()) {
						new_neighbor_potential_tiles.push_back(tile_info);
						continue;
					}

					neighbor_modified = true;
				}

				if (!neighbor_modified || neighbor->collapsed) {
					continue;
				}

				neighbor->SetPotentialTiles(new_neighbor_potential_tiles);
				stack.push(neighbor);
			}
		}
	}

	std::vector<Tile*> Grid::FindNeighbors(int x, int y)
	{
		std::vector<Tile*> neighbors;

		if (x == 0 && y == 0) // Left-top corner
		{
			neighbors.push_back(grid[1][0]); // Right tile
			neighbors.push_back(grid[0][1]); // Below tile
		}
		else if (x == max_width - 1 && y == 0) // Right-top corner
		{
			neighbors.push_back(grid[x][1]); // Below tile
			neighbors.push_back(grid[x-1][0]); // Left tile
		}
		else if (x == 0 && y == max_height - 1) // Left-down corner
		{
			neighbors.push_back(grid[0][y-1]); // Above tile
			neighbors.push_back(grid[1][y]); // Right tile
		}
		else if (x == max_width - 1 && y == max_height - 1) // Right-down corner
		{
			neighbors.push_back(grid[x-1][y]);
			neighbors.push_back(grid[x][y-1]);
		}
		else if (x == 0) // Left side
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
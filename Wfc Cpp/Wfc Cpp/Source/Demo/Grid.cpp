#include "Grid.h"

#include "Tile.h"
#include "../Engine/Engine.h"

namespace Demo
{
	Grid* Grid::Instance()
	{
		static Grid* instance = new Grid();
		return instance;
	}

	void Grid::CreateGrid()
	{
		int size = 27;
		int x_offset = 192;
		int y_offset = 40;
		for (int x = 0; x < max_width; x++)
		{
			for (int y = 0; y < max_height; y++)
			{
				int real_x = x_offset + x * size;
				int real_y = y_offset + y * size;

				Engine::Instance()->CreateObject(new Tile(glm::vec2(real_x, real_y), glm::vec2(2), 0, "empty-tile", 16, 16, false, 0));
			}
		}
	}
}
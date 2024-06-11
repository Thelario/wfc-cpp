#include "Tile.h"

#include "../Engine/Engine.h"
#include "../Engine/InputManager.h"
#include "../Engine/LoggerManager.h"

#include "Grid.h"

namespace Demo
{
	Tile::Tile(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, int x, int y) : GameObject(position, scale, rotation, texture_id,
			width, height, flip_x, tile_id, center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag), x(x), y(y)
	{
		default_scale = scale;
		current_tile_collapsed = nullptr;
		collapsed = false;

		TileInfo** tiles_array = TilesManager::Instance()->GetTilesInfoArray();
		for (int i = 0; i < TilesManager::Instance()->GetTilesInfoArraySize(); i++) {
			potential_tiles.push_back(tiles_array[i]);
		}

		potential_tiles_text = new Text(position, glm::vec2(0.08), std::to_string(potential_tiles.size()), "arial", true);
	}

	void Tile::Update()
	{
		GameObject::Update();

		glm::vec2 mouse_pos = InputManager::GetMousePosition();

		float real_width = width * scale.x;
		float real_height = height * scale.y;

		int pos_x = (center_aligned) ? (static_cast<int>(position.x - (real_width / 2))) : (position.x);
		int pos_y = (center_aligned) ? (static_cast<int>(position.y - (real_height / 2))) : (position.y);

		int edge_offset = 2;

		if ((pos_x + edge_offset < mouse_pos.x) &&
			(pos_x - edge_offset + real_width > mouse_pos.x) &&
			(pos_y + edge_offset < mouse_pos.y) &&
			(pos_y - edge_offset + real_height > mouse_pos.y))
		{
			if (collapsed == false) {
				tile_id = 1;
			}

			if (InputManager::GetMouseButtonDown(0) && collapsed == false) {
				Collapse();
			}
			else if (InputManager::GetMouseButtonDown(1) && collapsed == true) {
				EmptyTile();
			}
		}
		else if (collapsed == false) {
			tile_id = 0;
		}
	}

	void Tile::Render()
	{
		GameObject::Render();

		potential_tiles_text->Render();
	}

	std::vector<TileInfo*> Tile::GetPotentialTilesCopy() {
		std::vector<TileInfo*> copy;

		for (TileInfo* tile_info : potential_tiles) {
			copy.push_back(tile_info);
		}

		return copy;
	}

	void Tile::EmptyTile()
	{
		current_tile_collapsed = nullptr;
		texture_id = "empty-tile";
		tile_id = 0;
		scale = default_scale;
		collapsed = false;
	}

	void Tile::Collapse()
	{
		int max = potential_tiles.size() - 1;
		int rid = Engine::Instance()->GetRandom()->GenerateRandomInteger(0, max);
		current_tile_collapsed = potential_tiles[rid];
		potential_tiles.clear();
		potential_tiles.push_back(current_tile_collapsed);
		texture_id = current_tile_collapsed->texture_id;
		tile_id = current_tile_collapsed->id;
		scale = glm::vec2(scale.x * 0.85, scale.y * 0.85);
		collapsed = true;
		potential_tiles_text->enabled = false;
		Grid::Instance()->PropagateResult(x, y);
	}

	void Tile::Collapse(TileInfo* tile_info)
	{
		current_tile_collapsed = tile_info;
		collapsed = true;
	}

	void Tile::SetPotentialTiles(std::vector<TileInfo*> new_potential_tiles)
	{
		potential_tiles.clear();

		for (TileInfo* tile_info : new_potential_tiles) {
			potential_tiles.push_back(tile_info);
		}

		potential_tiles_text->SetText(std::to_string(potential_tiles.size()));
	}
}
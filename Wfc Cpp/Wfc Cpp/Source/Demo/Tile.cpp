#include "Tile.h"

#include "../Engine/Engine.h"

namespace Demo
{
	Tile::Tile(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag) : GameObject(position, scale, rotation, texture_id,
			width, height, flip_x, tile_id, center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag)
	{ }

	void Tile::Start()
	{
		EmptyTile();

		TileInfo** tiles_array = TilesManager::Instance()->GetTilesInfoArray();
		for (int i = 0; i < TilesManager::Instance()->GetTilesInfoArraySize(); i++) {
			potential_tiles.push_back(tiles_array[i]);
		}

		potential_tiles_text = new Text(position, glm::vec2(0.1), std::to_string(potential_tiles.size()), "arial", true);
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render()
	{
		GameObject::Render();

		potential_tiles_text->Render();
	}

	void Tile::EmptyTile()
	{
		current_tile_collapsed = nullptr;
		collapsed = false;
	}

	void Tile::Collapse()
	{
		current_tile_collapsed = potential_tiles[Engine::Instance()->GetRandom()->GenerateRandomInteger(0, potential_tiles.size())];
		collapsed = true;
	}

	void Tile::Collapse(TileInfo* tile_info)
	{
		current_tile_collapsed = tile_info;
		collapsed = true;
	}
}
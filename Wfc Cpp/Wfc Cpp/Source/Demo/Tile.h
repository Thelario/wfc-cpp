#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

#include "TilesManager.h"

using namespace Satellite;

namespace Demo
{
	class Tile : public GameObject
	{
		public:
			int id;
			bool collapsed;

			Text* potential_tiles_text;
			TileInfo* current_tile_collapsed;
			std::vector<TileInfo*> potential_tiles;

			Tile(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
				bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
				bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
				glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::NONE);

			void Start() override;
			void Update() override;
			void Render() override;

			void EmptyTile();
			void Collapse();
			void Collapse(TileInfo* tile_info);
	};
}
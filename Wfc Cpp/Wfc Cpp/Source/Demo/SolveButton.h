#pragma once

#include "../Engine/Button.h"

using namespace Satellite;

namespace Demo
{
	class SolveButton : public Button
	{
		public:
			SolveButton(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
				bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
				bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
				glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::NONE, glm::vec2 text_position = glm::vec2(0),
				glm::vec2 text_scale = glm::vec2(0), const std::string& text = "", bool text_enabled = true, const std::string& font_id = "arial");

			void OnMouseEnter() override;
			void OnMouseExit() override;
			void OnMouseStay() override;
	};
}
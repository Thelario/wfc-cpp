#include "ResetButton.h"

#include "../Engine/InputManager.h"
#include "Grid.h"

namespace Demo
{
	ResetButton::ResetButton(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, glm::vec2 text_position, glm::vec2 text_scale, const std::string& text,
		bool text_enabled, const std::string& font_id) : Button(position, scale, rotation, texture_id, width, height, flip_x, tile_id,
			center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag, text_position, text_scale, text, text_enabled, font_id)
	{ }

	void ResetButton::OnMouseEnter()
	{
		scale = glm::vec2(.9);
	}

	void ResetButton::OnMouseExit()
	{
		scale = glm::vec2(.75);
	}

	void ResetButton::OnMouseStay()
	{
		if (InputManager::GetMouseButtonDown(0)) {
			Grid::Instance()->Reset();
		}
	}
}
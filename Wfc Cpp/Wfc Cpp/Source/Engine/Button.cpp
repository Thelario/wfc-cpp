#include "Button.h"

namespace Satellite
{
	Button::Button(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, glm::vec2 text_position, glm::vec2 text_scale, const std::string& text,
		bool text_enabled, const std::string& font_id) : GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id,
			center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag)
	{
		button_text = new Text(text_position, text_scale, text, font_id, text_enabled);
	}

	Button::~Button()
	{
		delete button_text;
	}

	void Button::Start()
	{
		GameObject::Start();
	}

	void Button::Render()
	{
		GameObject::Render();
		button_text->Render();
	}
}
#include "Button.h"

#include "InputManager.h"
#include "LoggerManager.h"

namespace Satellite
{
	Button::Button(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, glm::vec2 text_position, glm::vec2 text_scale, const std::string& text,
		bool text_enabled, const std::string& font_id) : GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id,
			center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag)
	{
		button_text = new Text(text_position, text_scale, text, font_id, text_enabled);
		mouse_in = false;
	}

	Button::~Button()
	{
		delete button_text;
	}

	void Button::Start()
	{
		GameObject::Start();
	}

	void Button::Update()
	{
		glm::vec2 mouse_pos = InputManager::GetMousePosition();

		// Calculate real width and height based on scale.

		float real_width = width * scale.x;
		float real_height = height * scale.y;

		// Calculate correct position based on center alignment.

		int pos_x = (center_aligned) ? (static_cast<int>(position.x - (real_width / 2))) : (position.x);
		int pos_y = (center_aligned) ? (static_cast<int>(position.y - (real_height / 2))) : (position.y);

		// Applying mouse logic on buttons

		if ((position.x - real_width / 2) < mouse_pos.x &&
			(position.x + real_width / 2) > mouse_pos.x &&
			(position.y - real_height / 2) < mouse_pos.y &&
			(position.y + real_height / 2) > mouse_pos.y)
		{
			if (mouse_in == false)
			{
				mouse_in = true;
				OnMouseEnter();
			}
			else {
				OnMouseStay();
			}
		}
		else if (mouse_in == true)
		{
			mouse_in = false;
			OnMouseExit();
		}
	}

	void Button::Render()
	{
		GameObject::Render();
		button_text->Render();
	}
}
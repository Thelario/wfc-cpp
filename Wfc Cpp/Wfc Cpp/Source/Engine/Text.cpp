#include "Text.h"

#include <iostream>

#include "FontsManager.h"
#include "LoggerManager.h"
#include "Engine.h"

namespace Satellite
{
	Text::Text(glm::vec2 position, glm::vec2 scale, const std::string& text, const std::string& asset_id, bool enabled, SDL_Color color)
		: position(position), scale(scale), text(text), asset_id(asset_id), enabled(enabled), color(color),
		  font(FontsManager::Instance()->GetFont(asset_id))
	{ }

	void Text::SetText(std::string new_text) { text = new_text; }

	void Text::SetPosition(glm::vec2 new_position) { position = new_position; }

	void Text::SetScale(glm::vec2 new_scale) { scale = new_scale; }

	void Text::Render()
	{
		SDL_Renderer* renderer = Engine::Instance()->GetRenderer();

		if (font == nullptr) {
			LoggerManager::Error("The font with " + asset_id + " was not loaded correctly and is a nullptr.");
			return;
		}

		SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
		if (surface == NULL) {
			LoggerManager::Error("A problem occured when loading a surface from a font with " + asset_id, SDL_GetError());
			return;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == NULL) {
			LoggerManager::Error("A problem occured when loading a texture from surface in fonts " + asset_id, SDL_GetError());
			return;
		}

		int width = 0;
		int height = 0;

		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		float real_width = width * scale.x;
		float real_height = height * scale.y;

		SDL_Rect dst{
			static_cast<int>(position.x - (real_width / 2)),
			static_cast<int>(position.y - (real_height / 2)),
			real_width,
			real_height
		};

		SDL_RenderCopy(renderer, texture, NULL, &dst);

		SDL_DestroyTexture(texture);
	}
}
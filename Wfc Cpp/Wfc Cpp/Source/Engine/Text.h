#pragma once

#include <string>
#include <glm/glm.hpp>
#include <SDL_ttf.h>

#include "TexturesManager.h"

namespace Satellite
{
	class Text
	{
		public:
			bool enabled;
			glm::vec2 position;
			glm::vec2 scale;
			std::string text;
			std::string asset_id;
			SDL_Color color;
			TTF_Font* font;

		public:
			Text(glm::vec2 position, glm::vec2 scale, const std::string& text, const std::string& asset_id, bool enabled,
				SDL_Color color = { 255, 255, 255, 255 });

			void SetText(std::string new_text);
			void SetPosition(glm::vec2 new_position);
			void SetScale(glm::vec2 new_scale);

			void Render();
	};
}
#pragma once

#include <SDL.h>
#include <map>
#include <string>

#include "Texture.h"

namespace Satellite
{
	class TexturesManager
	{
		private:
			SDL_Renderer* _renderer;

			std::map<std::string, Texture*> _textures;

		public:
			static TexturesManager* Instance();

			bool Start(SDL_Renderer* renderer);
			void Destroy();

			SDL_Texture* GenerateTexture(const std::string& file_path);
			Texture* GetTexture(const std::string& texture_id) const;
	};
}
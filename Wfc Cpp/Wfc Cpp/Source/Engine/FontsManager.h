#pragma once

#include <map>
#include <string>
#include <SDL_ttf.h>

namespace Satellite
{
	class FontsManager
	{
		private:
			std::map<std::string, TTF_Font*> _fonts;

		public:
			static FontsManager* Instance();

			bool Start();
			void Destroy();

			bool AddFont(const std::string& asset_id, const std::string& file_path, int font_size);
			TTF_Font* GetFont(const std::string& asset_id) const;
	};
}
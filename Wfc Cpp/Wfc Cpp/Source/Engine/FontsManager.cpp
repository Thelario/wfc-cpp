#include "FontsManager.h"

#include "LoggerManager.h"

namespace Satellite
{
	const std::string path = "./Assets/Fonts/";

	FontsManager* FontsManager::Instance()
	{
		static FontsManager* instance = new FontsManager();
		return instance;
	}

	bool FontsManager::Start()
	{
		// Initializing TTF

		if (TTF_Init() != 0) {
			LoggerManager::Error("An error was produced when initializing TTF: ", TTF_GetError());
			return false;
		}

		return true;
	}

	void FontsManager::Destroy()
	{
		for (auto font : _fonts) {
			TTF_CloseFont(font.second);
		}

		_fonts.clear();
	}

	bool FontsManager::AddFont(const std::string& asset_id, const std::string& file_path, int font_size)
	{
		TTF_Font* font = TTF_OpenFont((path + file_path).c_str(), font_size);

		if (font == NULL) {
			LoggerManager::Error("A problem occure when opening font with " + asset_id, TTF_GetError());
			return false;
		}

		_fonts.emplace(asset_id, font);
	}

	TTF_Font* FontsManager::GetFont(const std::string& asset_id) const
	{
		if (_fonts.find(asset_id) == _fonts.end()) {
			LoggerManager::Error("Trying to get a font with a wrong asset id: " + asset_id);
			return nullptr;
		}

		return _fonts.at(asset_id);
	}
}
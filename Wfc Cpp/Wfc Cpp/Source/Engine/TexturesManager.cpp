#include "TexturesManager.h"

#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "LoggerManager.h"
#include "json.hpp"

using json = nlohmann::json;

namespace Satellite
{
	TexturesManager* TexturesManager::Instance()
	{
		static TexturesManager* instance = new TexturesManager();
		return instance;
	}

	bool TexturesManager::Start(SDL_Renderer* renderer)
	{
		if (renderer == nullptr) {
			LoggerManager::Error("The renderer provided in the Textures Manager is a nullptr.");
			return false;
		}

		_renderer = renderer;

		// Loading all the textures from the configuration file

		const std::string& config_file_name = "./Config/textures_config.json";

		std::ifstream file;

		file.open(config_file_name);

		if (file.fail() == true) {
			LoggerManager::Error("Failed to open file: " + config_file_name);
			return false;
		}

		json json_data = json::parse(file);

		std::string file_path = "./Assets/Images/";

		for (const auto& texture_json : json_data["textures"])
		{
			std::string texture_file_path = file_path + texture_json["name"].get<std::string>();

			SDL_Texture* texture = GenerateTexture(texture_file_path);

			Texture* my_texture = new Texture(texture, texture_json["width"], texture_json["height"], texture_json["tile_size"]);

			_textures.emplace(texture_json["asset_id"], my_texture);
		}

		file.close();
	}

	void TexturesManager::Destroy()
	{
		for (auto texture : _textures) {
			delete texture.second;
		}

		_textures.clear();
	}

	SDL_Texture* TexturesManager::GenerateTexture(const std::string& file_path)
	{
		// Create a surface based on the imgage file in the file path specified

		SDL_Surface* surface = IMG_Load(file_path.c_str());
		if (surface == NULL) {
			LoggerManager::Error("A problem occured when loading image with in file path " + file_path, SDL_GetError());
			return nullptr;
		}

		// Created a texture based on the surface

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (texture == NULL) {
			LoggerManager::Error("A problem occured when creating a texture from image in file path " + file_path, SDL_GetError());
			return nullptr;
		}

		SDL_FreeSurface(surface);

		return texture;
	}

	Texture* TexturesManager::GetTexture(const std::string& texture_id) const
	{
		if (_textures.find(texture_id) == _textures.end())
		{
			LoggerManager::Error("Trying to get a texture with a wrong texture id : " + texture_id);
			return nullptr;
		}

		return _textures.at(texture_id);
	}
}
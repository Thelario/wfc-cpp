#pragma once

#include <SDL.h>

namespace Satellite
{
	class Texture
	{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		int tile_size;

	public:
		Texture(SDL_Texture* texture, int width, int height);
		Texture(SDL_Texture* texture, int width, int height, int tile_size);
		~Texture();

		SDL_Texture* GetTexture() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetTileSize() const;
		const SDL_Rect GetSourceRect() const;
		const SDL_Rect GetTileSourceRect(int id) const;
	};
}
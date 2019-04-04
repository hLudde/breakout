#include "Block.h"

Block::Block(const Vector2 pos, SDL_Renderer* renderer): pos(pos), height(50), width(100) {
	rect.h = height;
	rect.w = width;
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0));

	CreateTexture(renderer);
}

Block::Block(const Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b, SDL_Renderer* renderer): pos(pos), height(h), width(w) {
	rect.h = height;
	rect.w = width;
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format,r,g,b));

	CreateTexture(renderer);
}

void Block::CreateTexture(SDL_Renderer* renderer)
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

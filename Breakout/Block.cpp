#include "Block.h"

Block::Block(Vector2 pos): pos(pos), height(50), width(100), rect() {
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = height;
	rect.w = width;
	surface = SDL_CreateRGBSurface(0, width, height, 0, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0));
}

Block::Block(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b): pos(pos), height(h), width(w), rect() {
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = height;
	rect.w = width;
	surface = SDL_CreateRGBSurface(0, width, height, 0, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format,r,g,b));
}

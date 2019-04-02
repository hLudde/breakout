#pragma once
#include <SDL.h>
#include "Vector2.h"

class Block {
public:
	explicit Block();
	explicit Block(Vector2 pos);

	explicit Block(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);

	SDL_Surface* GetSurface() const { return surface; }
	Vector2* GetPos() { return &pos; }
	int GetHeight() const { return height; }
	int GetWidth() const { return width; }

private:
	Vector2 pos;
	SDL_Rect rect{};
	int height, width;
	SDL_Surface* surface;

};

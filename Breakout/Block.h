#pragma once
#include <SDL.h>
#include "Vector2.h"

class Block {
public:
	explicit Block(Vector2 pos);

	explicit Block(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);

	SDL_Surface* GetSurface() const {
		return surface;
	}
protected:
	Vector2 pos;
	int height, width;
	SDL_Surface* surface;

private:
	SDL_Rect rect;

};

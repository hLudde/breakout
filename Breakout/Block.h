#pragma once
#include <SDL.h>
#include "Vector2.h"

class Block {
public:
	explicit Block() = default;
	explicit Block(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);

	/**
	 *Should not be used. use GetTexture() instead.
	 *When this is not used, should call SDL_FreeSurface() in CreateTexture()
	 */
	SDL_Texture* GetTexture() const { return texture; }
	Vector2* GetPos() { return &pos; }
	int GetHeight() const { return height; }
	int GetWidth() const { return width; }
	int GetRendererID() { return rendererID;  }

private:
	Vector2 pos;
	SDL_Rect* rect;
	int height, width;
	int rendererID;
	SDL_Surface* surface;
	SDL_Texture* texture = nullptr;
};

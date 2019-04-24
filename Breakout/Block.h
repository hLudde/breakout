#pragma once
#include <SDL.h>
#include "Vector2.h"
#include <vector>

class Block {
public:
	explicit Block() = default;
	explicit Block(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);
	explicit Block(Vector2 pos, int h, int w, int hp);

	Vector2* GetPos() { return &pos; }
	int GetHeight() const { return height; }
	int GetWidth() const { return width; }
	int GetRendererID() const { return rendererID;  }
	int GetHp() const { return hp; }

	void DecHp();

private:
	Vector2 pos;
	SDL_Rect* rect;
	int height, width;
	int rendererID;
	int hp;
};

#include "Block.h"
#include "Renderer.h"

Block::Block( Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b): pos(pos), height(h), width(w), hp(-1) {
	Renderer& renderer = Renderer::GetInstance();
	rect = new SDL_Rect{static_cast<int>(this->pos.x), static_cast<int>(this->pos.y), width, height };
	rendererID = renderer.CreateRectangle(rect, r, g, b, &this->pos);
}

Block::Block(Vector2 pos, int h, int w, int hp): pos(pos), height(h), width(w), hp(hp) {
	Renderer& renderer = Renderer::GetInstance();
	rect = new SDL_Rect{ static_cast<int>(this->pos.x), static_cast<int>(this->pos.y), width, height };

	int r = 0, g = 0, b = 0;
	switch (hp) {
		case 1: r = 255; g = 0; b = 0;
			break;
		case 2: r = 0; g = 0; b = 255;
			break;
		case 3: r = 0; g = 255; b = 0;
			break;
		default: r = 64, g = 64; b = 64;
	}
	rendererID = renderer.CreateRectangle(rect, r, g, b, &this->pos);
}

void Block::DecHp() {
	hp--;

	Uint8 r = 0, g = 0, b = 0;
	switch (hp) {
		case 1: r = 255; g = 0; b = 0;
			break;
		case 2: r = 0; g = 0; b = 255;
			break;
		case 3: r = 0; g = 255; b = 0;
			break;
		default: r = 64; g = 64; b = 64;
	}
	Renderer::GetInstance().ChangeRectangleColor(rendererID, r, g, b);
}

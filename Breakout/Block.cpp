#include "Block.h"
#include "Renderer.h"

Block::Block( Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b): pos(pos), height(h), width(w) {
	Renderer& renderer = Renderer::GetInstance();
	rect = new SDL_Rect{static_cast<int>(this->pos.x), static_cast<int>(this->pos.y), width, height };
	printf("new block at x:%d y:%d h:%d w:%d!\n", rect->x, rect->y, rect->h,rect->w);
	rendererID = renderer.CreateRectangle(rect, r, g, b, &this->pos);
}
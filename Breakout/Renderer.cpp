#include "Renderer.h"
Renderer::Renderer(SDL_Window* &window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x23, 0x7C, 0x42, 255);
	SDL_RenderDrawRect(renderer, new SDL_Rect{ 0,0, 100, 100});
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Renderer::CreateRectangle(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, new SDL_Rect{ x, y, width, height }, SDL_MapRGB(surface->format, r, g, b));
	textures.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	SDL_FreeSurface(surface);
}

void Renderer::Render() {
	for (SDL_Texture* texture : textures) {
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	}
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

}

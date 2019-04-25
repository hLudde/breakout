#include "Renderer.h"
#include "Vector2.h"

Renderer::Renderer(SDL_Window* &window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	printf("Created an instance of renderer!\n");
}

int Renderer::CreateRectangle(SDL_Rect* rectangle, Uint8 r, Uint8 g, Uint8 b, Vector2* pos) {
	const int rendererID = renderIDCounter++;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, rectangle->w, rectangle->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b));
	positions.push_back(pos);
	rectangles.push_back(rectangle);
	textures.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	renderObjects.push_back((rendererID));
	SDL_FreeSurface(surface);
	return rendererID;
}

void Renderer::DeleteRectangle(int id) {
	int position = 0;
	int initialized = false;
	for(unsigned int i = 0; renderObjects.size()>i; i++) {
		if(renderObjects.at(i)==id) {
			position = i;
			initialized = true;
		}
	}
	if(!initialized) {
		throw "RendererID requested to delete do not exist!";
	}
	renderObjects.erase(renderObjects.begin() + position);
	positions.erase(positions.begin() + position);
	rectangles.erase(rectangles.begin() + position);
	textures.erase(textures.begin() + position);
}

void Renderer::Render() {
	SDL_Rect rect{};
	for(int i = 0; static_cast<int>(textures.size()) > i; i++) {
		rect.x = static_cast<int>(positions.at(i)->x);
		rect.y = static_cast<int>(positions.at(i)->y);
		rect.w = rectangles.at(i)->w;
		rect.h = rectangles.at(i)->h;
		SDL_RenderCopy(renderer, textures.at(i), nullptr, &rect);
	}
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

}

void Renderer::ChangeRectangleColor(int id, Uint8 r, Uint8 g, Uint8 b) {
	int index = -1;
	for (int i = 0; i < renderObjects.size(); i++) {
		if (renderObjects.at(i) == id){
			index = i;
			break;
		}
	}

	SDL_Rect* rect = rectangles[index];
	SDL_Surface* surf = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surf, nullptr, SDL_MapRGB(surf->format, r, g, b));

	textures[index] = SDL_CreateTextureFromSurface(renderer, surf);
}

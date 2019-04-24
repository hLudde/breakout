#pragma once
#include <vector>
#include <SDL.h>

class Vector2;

class Renderer {
private:
	int renderIDCounter = 0;
	std::vector<int>renderObjects;
	explicit Renderer(SDL_Window* &window);
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect*> rectangles;
	SDL_Renderer* renderer;
	std::vector<Vector2*> positions;
public:

	static Renderer& GetInstance() {
		return InstanceImp();
	}

	static Renderer& InstanceImp(SDL_Window* window = nullptr) {
		static Renderer instance{ window };
		return instance;
	}

	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;

	static Renderer& Init(SDL_Window* &window) { return Renderer::InstanceImp(window); };


	int CreateRectangle(SDL_Rect* rectangle, Uint8 r, Uint8 g, Uint8 b, Vector2* pos);
	void DeleteRectangle(int id);
	void Render();

	void ChangeRectangleColor(int id, Uint8 r, Uint8 g, Uint8 b);
};

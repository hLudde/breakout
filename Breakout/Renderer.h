#pragma once
#include <vector>
#include <SDL.h>

class Renderer {
private:
	explicit Renderer(SDL_Window* &window);
	std::vector<SDL_Texture*> textures;
	SDL_Renderer* renderer;
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


	void CreateRectangle(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
	void Render();
};

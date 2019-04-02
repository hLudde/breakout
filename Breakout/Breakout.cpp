
#include <SDL.h>
#include <iostream>
#include "InputManager.h"

/*two global variables just to set screen size*/
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 750+50;

/*Function signatures*/
bool Init(SDL_Window* &window, SDL_Surface* &screenSurface);
void Close(SDL_Window* &window);
int LoadAndDisplayImage(SDL_Window* &window, SDL_Surface* &screenSurface);

/*main*/
int main(int argc, char* argv[]) {

	/*Create window and surface variables*/
	SDL_Window* appWindow = nullptr;
	SDL_Surface* appScreenSurface = nullptr;

	/*initialise SDL*/
	if (!Init(appWindow, appScreenSurface)) {
		Close(appWindow);
		return 0;
	};

	/*Prepare render and run game*/
	std::cout << "Window : " << appWindow << " Created!" << std::endl;
	LoadAndDisplayImage(appWindow, appScreenSurface);
	Close(appWindow);
	return 0;
}

/*initializing function for SDL*/
bool Init(SDL_Window* &window, SDL_Surface* &screenSurface) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("Breakout!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			printf("SDL could not create a window! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
		//SDL_SetWindowResizable(window, SDL_TRUE);
	}
	return success;
}

/*renderer init and gameLoop*/
int LoadAndDisplayImage(SDL_Window* &window, SDL_Surface* &screenSurface) {

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		Close(window);
		return EXIT_FAILURE;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* surface = SDL_LoadBMP("Pumpkin.bmp");
	if (surface == nullptr) {
		std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
		Close(window);
		return EXIT_FAILURE;
	}

	SDL_Texture* drawable = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect coords;

	coords.h = surface->h;
	coords.w = surface->w;
	coords.x = 0;
	coords.y = 0;
	float x = 0.0f;
	float y = SCREEN_HEIGHT-150;
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last;
	double deltaTime = 0;
	const float speed = .5f;

	SDL_FreeSurface(surface);
	/*renderer init STOP*/

	InputManager& inputManager = InputManager::GetInstance();

	/*GameLoop*/
	while (true) {
		/*Input manager*/
		last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = static_cast<double>(now - last)*1000 / SDL_GetPerformanceFrequency();
		inputManager.Update();
		std::cout << deltaTime << std::endl;
		/*if (inputManager.KeyStillDown(SDL_SCANCODE_UP)) {
			y -= speed * (float)deltaTime;
		}
		if (inputManager.KeyStillDown(SDL_SCANCODE_DOWN)) {
			y += speed * (float)deltaTime;
		}*/
		if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
			x -= speed * static_cast<float>(deltaTime);
		}
		if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
			x += speed * static_cast<float>(deltaTime);
		}
		if (inputManager.MouseDown(SDL_BUTTON_LEFT)) {

			std::cout << "You clicked the left mouse button!" << std::endl;
		}
		if (inputManager.MouseUp(SDL_BUTTON_LEFT)) {

			std::cout << "You released the left mouse button!" << std::endl;
		}
		if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
			Close(window);
		}

		/*renderer*/
		coords.x = static_cast<int>(x);
		coords.y = static_cast<int>(y);
		SDL_RenderCopy(renderer, drawable, nullptr, &coords);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return EXIT_SUCCESS;
}

/*cleaner and exiting function*/
void Close(SDL_Window* &window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
	return;
}
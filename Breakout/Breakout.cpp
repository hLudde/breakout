#include <SDL.h>
#include <iostream>
#include "InputManager.h"
#include "Timer.h"
#include "Player.h"
#include "Block.h"

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

	SDL_Surface* surface = Block(Vector2(),50,100,127,127,127).GetSurface();
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
	Player player = Player();
	float y = SCREEN_HEIGHT-150;
	Timer& timer = Timer::GetInstance();

	SDL_FreeSurface(surface);
	/*renderer init STOP*/

	InputManager& inputManager = InputManager::GetInstance();

	/*GameLoop*/
	while (true) {
		/*Input manager*/
		timer.UpdateDeltaTime();
		inputManager.Update();
		//std::cout << timer.GetDeltaTime() << std::endl;
		player.MovePlayer();
		if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
			Close(window);
		}

		/*renderer*/
		coords.x = static_cast<int>(player.GetPos());
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
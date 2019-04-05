#include <SDL.h>
#include <iostream>
#include "InputManager.h"
#include "Timer.h"
#include "Vector2.h"
#include "Block.h"
#include "Player.h"
#include <vector>
#include "BrickLayer.h"
#include "Ball.h"
#include "Renderer.h"

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 25

/*two global variables just to set screen size*/
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 750+50;

/*Function signatures*/
bool Init(SDL_Window* &window, SDL_Surface* &screenSurface);
void Close(SDL_Window* &window);
int LoadAndDisplayImage(SDL_Window* &window, SDL_Surface* &screenSurface);
void RenderMap(SDL_Renderer* renderer, std::vector<Block>* map);

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
	return EXIT_SUCCESS;
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

	//Renderer& renderer = Renderer::Init(window);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	/*if (renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
	a	Close(window);
		return EXIT_FAILURE;
	}*/
	Player player = Player(Vector2((SCREEN_WIDTH-PLAYER_WIDTH)/2, SCREEN_HEIGHT-150), PLAYER_HEIGHT, PLAYER_WIDTH, 0x12, 0xF2, 0x5F,renderer, screenSurface->w);
	SDL_Surface* surface = player.GetSurface();//Block(Vector2(0 , SCREEN_HEIGHT - 150), PLAYER_HEIGHT, PLAYER_WIDTH, 255, 0,0).GetSurface();
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
	float y = SCREEN_HEIGHT-150;
	Timer& timer = Timer::GetInstance();

	SDL_FreeSurface(surface);
	/*renderer init STOP*/

	BrickLayer BL;
	BL.CreateMap(SCREEN_WIDTH, SCREEN_HEIGHT,renderer);
	std::vector<Block>* map = BL.GetMap();

	Ball ball{ Vector2{static_cast<int>(SCREEN_WIDTH / 2),500.0f},Vector2{1.0f,0.5f}, 10.0f,127,127,127,renderer };

	InputManager& inputManager = InputManager::GetInstance();

	/*GameLoop*/
	while (true) {
		/*Input manager*/

		timer.UpdateDeltaTime();
		inputManager.Update();
		player.MovePlayer();
		if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
			Close(window);
			return EXIT_SUCCESS;
		}
		/*if (ball.IsDead())
			Close(window);*/

		/*renderer*/

		RenderMap(renderer,map);

		ball.CheckCollision(SCREEN_HEIGHT,SCREEN_WIDTH,map,&player.GetBlock());
		ball.MoveBall();
		SDL_RenderCopy(renderer, ball.GetTexture(), nullptr, ball.GetRect());

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
	return;
}

void RenderMap(struct SDL_Renderer* renderer, std::vector<Block>* map)
{

	for (int i=0;i < map->size();i++)
	{
		Block& block = map->at(i);

		if (block.GetTexture() == nullptr)
			block.CreateTexture(renderer);

		SDL_Rect rect { int(block.GetPos()->x),int(block.GetPos()->y),block.GetWidth(),block.GetHeight() };
		SDL_RenderCopy(renderer, block.GetTexture(), nullptr, &rect);
	}
}
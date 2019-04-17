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
#include <future>

#define FPS_INTERVAL 1.0 //seconds.
#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 25

/*two global variables just to set screen size*/
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 750+50;

int lives = 3;

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
	}
	return success;
}

/*renderer init and gameLoop*/
int LoadAndDisplayImage(SDL_Window* &window, SDL_Surface* &screenSurface) {

	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_frames = 0; //frames passed since the last recorded fps.

	Renderer& renderer = Renderer::Init(window);
	Player player = Player(Vector2((SCREEN_WIDTH-PLAYER_WIDTH)/2, SCREEN_HEIGHT-150), PLAYER_HEIGHT, PLAYER_WIDTH, 0x12, 0xF2, 0x5F, screenSurface->w);
	InputManager& inputManager = InputManager::GetInstance();
	Timer&  timer = Timer::GetInstance();
	///*renderer init STOP*/

	BrickLayer BL;
	BL.CreateMap(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::vector<std::vector<Block*>>* map = BL.GetMap();

	Ball ball{ Vector2{static_cast<int>(SCREEN_WIDTH / 2) - 10.0f,500.0f},Vector2{0.0f,1.0f}, 10.0f,127,127,127 };

	bool pause = true;
	/*GameLoop*/
	while (true) {
		/*Input manager*/
		timer.UpdateDeltaTime();
		inputManager.Update();

		if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
			Close(window);
			break;
		}
		if (inputManager.KeyDown(SDL_SCANCODE_SPACE)) {
			pause = !pause;
		}
		if (ball.IsDead()){
			if(--lives <= 0) {
				Close(window);
				break;
			}
			ball.Reset(Vector2{ static_cast<int>(SCREEN_WIDTH / 2) - ball.GetRadius(),500.0f }, Vector2{ 0.0f,1.0f });
			pause = true;
		}

		if (!pause) {
			auto collisionCheck = std::future<void>(std::async([&ball, &map, &player] {
				ball.CheckCollision(SCREEN_HEIGHT, SCREEN_WIDTH, map, player.GetBlock());
			}));

			ball.MoveBall();

			player.MovePlayer();

			collisionCheck.wait();
		}

		renderer.Render();
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000)
		{
			fps_lasttime = SDL_GetTicks();
			printf("FPS: %d\n", fps_frames);
			fps_frames = 0;
		}
	}
	return EXIT_SUCCESS;
}

/*cleaner and exiting function*/
void Close(SDL_Window* &window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}
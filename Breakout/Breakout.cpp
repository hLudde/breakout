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
#define SCREEN_HEIGHT 750
#define SCREEN_WIDTH 800

/*Function signatures*/
bool InitializeSDL(SDL_Window* &window, SDL_Surface* &screenSurface);
void CloseSDL(SDL_Window* &window);
int RunGame(SDL_Window* &window, SDL_Surface* &screenSurface);

void CheckInput(SDL_Window* &window, InputManager& inputManager, bool &pause, bool &run);
void MovePlayerBall(Player &player, Ball &ball, std::vector<std::vector<Block*>>* &map);
void UpdateFPS(Uint32 & fpsLastTime, Uint32 & fpsFrames);
void ResetPlayerBall(Player &player, Ball &ball, bool &pause, bool &run);

/*main*/
int main(int argc, char* argv[]) {

	/*Create window and surface variables*/
	SDL_Window* appWindow = nullptr;
	SDL_Surface* appScreenSurface = nullptr;

	/*initialise SDL*/
	if (!InitializeSDL(appWindow, appScreenSurface)) {
		CloseSDL(appWindow);
		return EXIT_FAILURE;
	};
	/*Prepare render and run game*/
	std::cout << "Window : " << appWindow << " Created!" << std::endl;
	
	return RunGame(appWindow, appScreenSurface);;
}

/*initializing function for SDL*/
bool InitializeSDL(SDL_Window* &window, SDL_Surface* &screenSurface) {
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
int RunGame(SDL_Window* &window, SDL_Surface* &screenSurface) {

	Uint32 fpsLastTime = SDL_GetTicks(); //the last recorded time.
	Uint32 fpsFrames = 0; //frames passed since the last recorded fps.

	Renderer& renderer = Renderer::Init(window);
	Player player = Player(Vector2((SCREEN_WIDTH - PLAYER_WIDTH) / 2, SCREEN_HEIGHT - 150), PLAYER_HEIGHT, PLAYER_WIDTH, 0x12, 0xF2, 0x5F, screenSurface->w);
	InputManager& inputManager = InputManager::GetInstance();
	Timer&  timer = Timer::GetInstance();

	BrickLayer brickLayer;
	brickLayer.CreateMap(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::vector<std::vector<Block*>>* map = brickLayer.GetMap();

	Ball ball{ Vector2{static_cast<int>(SCREEN_WIDTH / 2) - 10.0f,450.0f},Vector2{0.0f,1.0f}, 10.0f,127,127,127 };

	bool run = true;
	bool pause = true;
	/*GameLoop*/
	while (run) {
		timer.UpdateDeltaTime();

		CheckInput(window, inputManager, pause, run);

		if (!pause)
			MovePlayerBall(player, ball, map);
		if (ball.IsDead())
			ResetPlayerBall(player, ball, pause, run);

		renderer.Render();
		UpdateFPS(fpsLastTime, fpsFrames);
	}

	CloseSDL(window);
	return EXIT_SUCCESS;
}

/*cleaner and exiting function*/
	void CloseSDL(SDL_Window* &window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void CheckInput(SDL_Window*& window, InputManager &inputManager, bool &pause, bool &run) {
	inputManager.Update();

	if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
		run = false;
	}
	if (inputManager.KeyDown(SDL_SCANCODE_SPACE)) {
		pause = !pause;
	}
}

void MovePlayerBall(Player &player, Ball &ball, std::vector<std::vector<Block*>>* &map) {
	auto collisionCheck = std::future<void>(std::async([&ball, &map, &player] {
		ball.CheckCollision(SCREEN_HEIGHT, SCREEN_WIDTH, map, player.GetBlock());
	}));

	ball.MoveBall();
	player.MovePlayer();
	collisionCheck.wait();
}

void UpdateFPS(Uint32 &fpsLastTime, Uint32 &fpsFrames) {
	fpsFrames++;

	if (fpsLastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
	{
		fpsLastTime = SDL_GetTicks();
		std::cout << "FPS: " << fpsFrames << std::endl;
		fpsFrames = 0;
	}
}

void ResetPlayerBall(Player& player, Ball& ball, bool &pause, bool &run) {
	player.DecrementLives();
	if (player.GetLives() <= 0) {
		run = false;
	}
	player.Reset();
	ball.Reset(Vector2{ static_cast<int>(SCREEN_WIDTH / 2) - ball.GetRadius(),450.0f }, Vector2{ 0.0f,1.0f });
	pause = true;
}

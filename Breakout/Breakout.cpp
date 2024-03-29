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

void CheckInput(InputManager& inputManager, bool &pause, bool &run);
void UpdateFPS(Uint32 & fpsLastTime, Uint32 & fpsFrames);
void ResetPlayerBall(Player &player, Ball &ball, bool &pause, bool &run);
void CollisionCheck(Ball &ball, std::vector<Block*>* &map, Player &player);

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

/*game init and gameLoop*/
int RunGame(SDL_Window* &window, SDL_Surface* &screenSurface) {

	Uint32 fpsLastTime = SDL_GetTicks(); //the last recorded time.
	Uint32 fpsFrames = 0; //frames passed since the last recorded fps.

	Renderer& renderer = Renderer::Init(window);
	Player player = Player(Vector2((SCREEN_WIDTH - PLAYER_WIDTH) / 2, SCREEN_HEIGHT - 150), PLAYER_HEIGHT, PLAYER_WIDTH, 0x12, 0xF2, 0x5F, screenSurface->w);
	InputManager& inputManager = InputManager::GetInstance();
	Timer&  timer = Timer::GetInstance();

	BrickLayer brickLayer;
	//brickLayer.CreateRandomMap(SCREEN_WIDTH, SCREEN_HEIGHT);
	brickLayer.CreateMapFromFile(SCREEN_WIDTH, SCREEN_HEIGHT, "map.txt");
	std::vector<Block*>* map = brickLayer.GetMap();

	Ball ball{ Vector2{static_cast<int>(SCREEN_WIDTH / 2) - 10.0f,450.0f},Vector2{0.0f,1.0f}, 10.0f,127,127,127 };

	bool run = true;
	bool pause = true;
	std::future<void> collisionFuture;
	/*GameLoop*/
	while (run) {
		timer.UpdateDeltaTime();

		CheckInput(inputManager, pause, run);

		if (!pause) {
			player.MovePlayer();
			ball.MoveBall();
			collisionFuture = std::future<void>(std::async([&player, &ball, &map] {CollisionCheck(ball, map, player); }));
		}
		if (ball.IsDead()) {
			player.DecrementLives();
			ResetPlayerBall(player, ball, pause, run);
		}
		if (brickLayer.GetBlockCount() == 0) {
			brickLayer.CreateRandomMap(SCREEN_WIDTH, SCREEN_HEIGHT);
			map = brickLayer.GetMap();
			ResetPlayerBall(player, ball, pause, run);
		}

		if (collisionFuture.valid())
			collisionFuture.wait();

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

void CheckInput(InputManager &inputManager, bool &pause, bool &run) {
	inputManager.Update();

	if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
		run = false;
	}
	if (inputManager.KeyDown(SDL_SCANCODE_SPACE)) {
		pause = !pause;
	}
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
	if (player.GetLives() <= 0) {
		run = false;
	}
	player.Reset();
	ball.Reset(Vector2{ static_cast<int>(SCREEN_WIDTH / 2) - ball.GetRadius(),450.0f }, Vector2{ 0.0f,1.0f });
	pause = true;
}

void CollisionCheck(Ball &ball, std::vector<Block*>*& map, Player &player) {
	ball.CheckCollision(SCREEN_HEIGHT, SCREEN_WIDTH, map, player.GetBlock());
}

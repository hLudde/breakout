// Breakout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include "pch.h"
#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "InputManager.h"

/*two global variables just to set screen size*/
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 750+50;

/*Function signatures*/
bool init(SDL_Window* &window, SDL_Surface* &screenSurface);
void close(SDL_Window* &window);
int loadAndDiplayImage(SDL_Window* &window, SDL_Surface* &screenSurface);

/*main*/
int main(int argc, char* args[]) {

	/*Create window and surface variables*/
	SDL_Window* appWindow = NULL;
	SDL_Surface* appScreenSurface = NULL;

	/*initialise SDL*/
	if (!init(appWindow, appScreenSurface)) {
		close(appWindow);
		return 0;
	};

	/*Prepare render and run game*/
	std::cout << "Window : " << appWindow << " Created!" << std::endl;
	loadAndDiplayImage(appWindow, appScreenSurface);
	close(appWindow);
	return 0;
}

/*initializing function for SDL*/
bool init(SDL_Window* &window, SDL_Surface* &screenSurface) {
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

/*renderer init and gameloop*/
int loadAndDiplayImage(SDL_Window* &window, SDL_Surface* &screenSurface) {

	/*renderer init START*/
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		close(window);
		return EXIT_FAILURE;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* surface = SDL_LoadBMP("Pumpkin.bmp");
	if (surface == nullptr) {
		std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
		close(window);
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
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	float speed = .5f;

	SDL_FreeSurface(surface);
	/*renderer init STOP*/

	InputManager& inputManager = InputManager::getInstance();

	/*Gameloop*/
	while (true) {
		/*Input manager*/
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)(NOW - LAST)*1000 / SDL_GetPerformanceFrequency();
		inputManager.Update();
		std::cout << deltaTime << std::endl;
		/*if (inputManager.KeyStillDown(SDL_SCANCODE_UP)) {
			y -= speed * (float)deltaTime;
		}
		if (inputManager.KeyStillDown(SDL_SCANCODE_DOWN)) {
			y += speed * (float)deltaTime;
		}*/
		if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
			x -= speed * (float)deltaTime;
		}
		if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
			x += speed * (float)deltaTime;
		}
		if (inputManager.MouseDown(SDL_BUTTON_LEFT)) {

			std::cout << "You clicked the left mouse button!" << std::endl;
		}
		if (inputManager.MouseUp(SDL_BUTTON_LEFT)) {

			std::cout << "You released the left mouse button!" << std::endl;
		}
		if (inputManager.KeyUp(SDL_SCANCODE_ESCAPE)) {
			close(window);
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
void close(SDL_Window* &window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
	return;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

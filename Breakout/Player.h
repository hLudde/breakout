#pragma once
#include "Block.h"
class Player {
public:
	Player(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);
	void MovePlayer();
	float GetPos() const;
	SDL_Surface* GetSurface() const;
private:
	Block player;
	float x = 0;
	float playerSpeed = .5f;
	Timer& timer = Timer::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	
};
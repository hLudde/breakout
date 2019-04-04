#pragma once

class Player {
public:
	Player(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b,SDL_Renderer* renderer);
	void MovePlayer();
	float GetPos();
	SDL_Surface* GetSurface() const;
	Block GetBlock() const { return player; }
private:
	float playerSpeed = .5f;
	Timer& timer = Timer::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	Block player;
};

#pragma once

class Player {
public:
	Player(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b);
	void MovePlayer();
	float GetPos();
	SDL_Surface* GetSurface() const;
private:
	float playerSpeed = .5f;
	Timer& timer = Timer::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	Block player;
};

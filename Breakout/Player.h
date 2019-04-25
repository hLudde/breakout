#pragma once
#include "Renderer.h"
class Player {
public:
	Player(Vector2 pos, int h, int w, Uint8 r, Uint8 g, Uint8 b, int screenWidth);
	void MovePlayer() const;
	float GetPos() const;
	Block* GetBlock() const { return player; }
	void Reset() const { player->GetPos()->x = 350.0f; }
	int GetLives() const { return lives; }
	void DecrementLives() { lives--; Renderer::GetInstance().DeleteRectangle(HealthRenderIds.back()); HealthRenderIds.pop_back();  }
	std::vector<int> HealthRenderIds;

private:
	float playerSpeed = .5f;
	const int w;
	Timer& timer = Timer::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	Block* player;
	int lives{ 3 };
};

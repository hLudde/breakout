#pragma once
class Player {
public:
	void MovePlayer();
	int GetPos() const;
private:
	float x = 0;
	float playerSpeed = .5f;
	Timer& timer = Timer::GetInstance();
	InputManager& inputManager = InputManager::GetInstance();
	
};
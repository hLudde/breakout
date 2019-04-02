#include <SDL.h>
#include "InputManager.h"
#include "Timer.h"
#include "Player.h"

void Player::MovePlayer() {
	if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
		x -= playerSpeed * static_cast<float>(timer.GetDeltaTime());
	}
	if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
		x += playerSpeed * static_cast<float>(timer.GetDeltaTime());
	}
}

int Player::GetPos() const {
	return x;
}

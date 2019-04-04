#include <SDL.h>
#include "InputManager.h"
#include "Timer.h"
#include "Block.h"
#include "Player.h"
Player::Player(const Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b, SDL_Renderer* renderer)
{
	player = Block{ pos, h, w, r, g, b,renderer };
}

SDL_Surface* Player::GetSurface() const {
	return player.GetSurface();
}

void Player::MovePlayer() {
	if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
		player.GetPos()->x -= playerSpeed * static_cast<float>(timer.GetDeltaTime());
	}
	if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
		player.GetPos()->x += playerSpeed * static_cast<float>(timer.GetDeltaTime());
	}
}

float Player::GetPos(){
	return player.GetPos()->x;
}

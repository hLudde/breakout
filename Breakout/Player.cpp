#include <SDL.h>
#include "InputManager.h"
#include "Timer.h"
#include "Block.h"
#include "Player.h"
Player::Player(const Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b, SDL_Renderer* renderer, const int screenWidth): w(screenWidth)
{
	player = Block{ pos, h, w, r, g, b,renderer };
}

SDL_Surface* Player::GetSurface() const {
	return player.GetSurface();
}

void Player::MovePlayer() {
	float &x = player.GetPos()->x;
	if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
		x -= playerSpeed * static_cast<float>(timer.GetDeltaTime());
		if (x <= 0) {
			x = 0;
		}
	}
	if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
		x += playerSpeed * static_cast<float>(timer.GetDeltaTime());
		if (x + player.GetWidth() >= w) {
			x = static_cast<float>(w - player.GetWidth());
		}
	}
}

float Player::GetPos(){
	return player.GetPos()->x;
}

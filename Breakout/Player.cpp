#include <SDL.h>
#include "InputManager.h"
#include "Timer.h"
#include "Block.h"
#include "Player.h"
#include "Renderer.h"
Player::Player(const Vector2 pos, const int h, const int w, const Uint8 r, const Uint8 g, const Uint8 b, const int screenWidth): w(screenWidth)
{
	player = new Block{ pos, h, w, r, g, b};
	HealthRenderIds.push_back(Renderer::GetInstance().CreateRectangle(new SDL_Rect{ 0,0, 10,10 }, 255, 0, 0, new Vector2(700, 700)));
	HealthRenderIds.push_back(Renderer::GetInstance().CreateRectangle(new SDL_Rect{ 0,0, 10,10 }, 255, 0, 0, new Vector2(720, 700)));
	HealthRenderIds.push_back(Renderer::GetInstance().CreateRectangle(new SDL_Rect{ 0,0, 10,10 }, 255, 0, 0, new Vector2(740, 700)));
}

void Player::MovePlayer() const
{
	Vector2* pos = player->GetPos();
	if (inputManager.KeyStillDown(SDL_SCANCODE_LEFT)) {
		pos->x -= playerSpeed * static_cast<float>(timer.GetDeltaTime());
		if (pos->x <= 0) {
			pos->x = 0;
		}
	}
	if (inputManager.KeyStillDown(SDL_SCANCODE_RIGHT)) {
		pos->x += playerSpeed * static_cast<float>(timer.GetDeltaTime());
		if (pos->x + player->GetWidth() >= w) {
			pos->x = static_cast<float>(w - player->GetWidth());
		}
	}
}

float Player::GetPos() const
{
	return player->GetPos()->x;
}

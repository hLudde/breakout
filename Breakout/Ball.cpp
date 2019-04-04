#include "Ball.h"
#include "Timer.h"

Ball::Ball(Vector2 pos, Vector2 dir, float radius, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer): dir(dir), pos(pos), radius(radius)
{
	speed = 0.5f;

	rect.w = radius * 2;
	rect.h = radius * 2;

	auto surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

void Ball::CheckCollision(int winHeight, int winWidth, std::vector<Block>* map)
{
	if (pos.x - radius < 0 || pos.x + radius > winWidth)
		dir.x = -dir.x;
	if (pos.y - radius < 0 || pos.y + radius > winHeight)
		dir.y = -dir.y;

	dir = dir.Normalize();
}

void Ball::MoveBall()
{
	const float distance = speed * timer.GetDeltaTime();

	pos.x += dir.x * distance;
	pos.y += dir.y * distance;

	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
}

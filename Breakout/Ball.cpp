#include "Ball.h"
#include "Timer.h"
#include <iostream>

Ball::Ball(Vector2 pos, Vector2 dir, float radius, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer): dir(dir), pos(pos), radius(radius)
{
	speed = 0.5f;
	diameter = radius * 2;

	rect.w = diameter;
	rect.h = diameter;

	auto surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

void Ball::CheckCollision(const int winHeight, const int winWidth, std::vector<Block>* map, Block* player)
{
	if (pos.x < 0 || pos.x + diameter > winWidth)
		dir.x = -dir.x;
	if (pos.y < 0 || pos.y + diameter> winHeight)
		dir.y = -dir.y;

	for (int i=0; i < map->size();i++)
	{
		if(IsColliding(&map->at(i)))
		{
			std::cout << "Colliding!" << std::endl;
			ChangeDir(&map->at(i));
			break;
		}
	}

	if (IsColliding(player))
	{
		ChangeDir(player);
	}

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

bool Ball::IsColliding(Block* block) const
{
	int bx1 = block->GetPos()->x;
	int bx2 = bx1 + block->GetWidth();
	int by1 = block->GetPos()->y;
	int by2 = by1 + block->GetHeight();

	if ((pos.x > bx1 && pos.x < bx2) || (pos.x + diameter > bx1 && pos.x + diameter < bx2))
		if ((pos.y > by1 && pos.y < by2) || (pos.y + diameter > by1 && pos.y + diameter < by2))
			return true;
	return false;
}

void Ball::ChangeDir(Block* block)
{
	const Vector2 bPos = *block->GetPos();
	const Vector2 center = pos + Vector2{ radius,radius };

	if (center.x <= bPos.x || center.x >= bPos.x + block->GetWidth())
		dir.x = -dir.x;
	else
		dir.y = -dir.y;
}

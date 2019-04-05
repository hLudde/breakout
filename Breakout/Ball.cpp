#include "Ball.h"
#include "Timer.h"
#include <iostream>

Ball::Ball(Vector2 pos, Vector2 dir, float radius, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer): dir(dir), pos(pos), radius(radius)
{
	speed = 0.5f;
	diameter = radius * 2;
	oldPos = pos;

	rect.w = static_cast<int>(diameter);
	rect.h = static_cast<int>(diameter);

	auto surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

void Ball::MoveBall()
{
	oldPos = pos;

	const float distance = speed * static_cast<float>(timer.GetDeltaTime());

	pos.x += dir.x * distance;
	pos.y += dir.y * distance;

	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
}

void Ball::CheckCollision(const int winHeight, const int winWidth, std::vector<Block>* map, Block* player)
{
	WallCollide(winWidth, winHeight);

	for (int i=0; i < map->size();i++)
	{
		if(IsColliding(&map->at(i)))
		{
			std::cout << "Colliding; Block" << std::endl;
			ChangeDir(&map->at(i));
			map->erase(map->begin() + i);
			break;
		}
	}

	if (IsColliding(player))
	{
		ChangeDir(player);
	}

	dir = dir.Normalize();
}

void Ball::WallCollide(int winWidth, int winHeight)
{
	if (pos.x <= 0) {
		dir.x = abs(dir.x);
		std::cout << "Colliding; Left" << std::endl;
	}

	else if (pos.x + diameter >= winWidth) {
		dir.x = -abs(dir.x);
		std::cout << "Colliding; Right" << std::endl;
	}

	if (pos.y <= 0) {
		dir.y = abs(dir.y);
		std::cout << "Colliding; Up" << std::endl;
	}
	else if (pos.y + diameter >= winHeight) {
		dir.y = -abs(dir.y);
		std::cout << "Colliding; Down" << std::endl;
	}

}

bool Ball::IsColliding(Block* block) const
{
	const int left = static_cast<int>(block->GetPos()->x);
	const int right = left + block->GetWidth();
	const int up = static_cast<int>(block->GetPos()->y);
	const int down = up + block->GetHeight();

	if ((pos.x >= left && pos.x <= right) || (pos.x + diameter >= left && pos.x + diameter <= right))
		if ((pos.y >= up && pos.y <= down) || (pos.y + diameter >= up && pos.y + diameter <= down))
			return true;
	return false;
}

void Ball::ChangeDir(Block* block)
{
	if (CollidedFromLeft(block))
		dir.x = -abs(dir.x);
	else if (CollidedFromRight(block))
		dir.x = abs(dir.x);

	if (CollidedFromUp(block))
		dir.y = -abs(dir.y);
	else if (CollidedFromDown(block))
		dir.y = abs(dir.y);

}

bool Ball::CollidedFromLeft(Block* block) const
{
	return pos.x + diameter >= block->GetPos()->x && oldPos.x + diameter < block->GetPos()->x;
}

bool Ball::CollidedFromRight(Block* block) const
{
	return pos.x <= block->GetPos()->x + block->GetWidth() && oldPos.x > block->GetPos()->x + block->GetWidth();
}

bool Ball::CollidedFromUp(Block* block) const
{
	return pos.y + diameter >= block->GetPos()->y && oldPos.y + diameter < block->GetPos()->y;
}

bool Ball::CollidedFromDown(Block* block) const
{
	return pos.y <= block->GetPos()->y + block->GetHeight() && oldPos.y > block->GetPos()->y + block->GetHeight();
}

#include "Ball.h"
#include "Timer.h"
#include "Renderer.h"
#include <iostream>

Ball::Ball(Vector2 pos, Vector2 dir, float radius, Uint8 r, Uint8 g, Uint8 b): dir(dir), pos(pos), radius(radius)
{
	speed = 0.5f;
	diameter = radius * 2;
	oldPos = pos;

	rect.w = static_cast<int>(diameter);
	rect.h = static_cast<int>(diameter);

	Renderer::GetInstance().CreateRectangle(&rect, r,g,b, &this->pos);
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

void Ball::CheckCollision(const int winHeight, const int winWidth, std::vector<Block*>* map, Block* player)
{
	if (static_cast<int>(pos.y) < winHeight/2) 
	{
		for (int i = 0; i < map->size(); i++) {
			Block* b = map->at(i);
			if (IsColliding(b)) {
				ChangeDir(b);

				if (b->GetHp() >= 0) {
					b->DecHp();

					if (b->GetHp() == 0) {
						map->erase(std::begin(*map) + i);
						Renderer::GetInstance().DeleteRectangle(b->GetRendererID());
					}
				}
			}
		}
	}

	if (pos.y > winHeight/2 && IsColliding(player))
		PlayerCollide(player);

	WallCollide(winWidth, winHeight);

	dir = dir.Normalize();
}

void Ball::WallCollide(const int winWidth, const int winHeight)
{
	if (pos.x <= 0) {
		dir.x = abs(dir.x);
	}

	else if (pos.x + diameter >= winWidth) {
		dir.x = -abs(dir.x);
	}

	if (pos.y <= 0) {
		dir.y = abs(dir.y);
	}
	else if (pos.y + diameter >= winHeight) {
		isDead = true;
		dir.y = -abs(dir.y);
	}
}

//special collision system for the pad. Reflection angle is the vector from the pads center to the balls center.
void Ball::PlayerCollide(Block* block)
{
	const Vector2 bCenter = pos + Vector2{ radius,radius };
	const Vector2 pCenter = *block->GetPos() + Vector2{ static_cast<float>(block->GetWidth()) / 2,static_cast<float>(block->GetHeight()) / 2 };

	Vector2 newDir = bCenter - pCenter;
	newDir = newDir.Normalize();

	dir = newDir;
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

//4 functions checks current position colliding and old position not colliding
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

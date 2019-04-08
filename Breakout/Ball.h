#pragma once
#include "Block.h"
#include <vector>
#include "Timer.h"

class Ball
{
public:
	Ball(Vector2 pos, Vector2 dir, float radius, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer);

	float GetSpeed() const { return speed; }
	float GetRadius() const { return radius; }
	Vector2 GetDir() const { return dir; }
	Vector2 GetPos() const { return pos; }
	SDL_Texture* GetTexture() const { return texture; }
	SDL_Rect* GetRect() { return &rect; }

	void CheckCollision(int winHeight, int winWidth, std::vector<std::vector<Block>>* map, Block* player);
	void MoveBall();
	bool IsColliding(Block* block) const;
	bool IsDead() const { return isDead; }
private:
	Vector2 dir;
	Vector2 pos;
	Vector2 oldPos;
	float speed;
	float radius;
	float diameter;
	SDL_Rect rect{};
	SDL_Texture* texture;
	Timer& timer = Timer::GetInstance();

	bool isDead = false;

	void ChangeDir(Block* block);
	void WallCollide(int winWidth, int winHeight);
	void PlayerCollide(Block* block);

	bool CollidedFromLeft(Block* block) const;
	bool CollidedFromRight(Block* block) const;
	bool CollidedFromUp(Block* block) const;
	bool CollidedFromDown(Block* block) const;
};

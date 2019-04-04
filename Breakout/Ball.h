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

	void CheckCollision(int winHeight, int winWidth, std::vector<Block>* map);
	void MoveBall();
private:
	Vector2 dir;
	Vector2 pos;
	float speed;
	float radius;
	SDL_Rect rect{};
	SDL_Texture* texture;
	Timer& timer = Timer::GetInstance();
};

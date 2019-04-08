#pragma once
#include "Block.h"
#include <vector>

class BrickLayer
{
public:
	BrickLayer() = default;

	void CreateMap(int windowWidth, int windowHeight, SDL_Renderer* renderer);

	std::vector<std::vector<Block>>* GetMap() { return &map; }
private:
	std::vector<std::vector<Block>> map;
};

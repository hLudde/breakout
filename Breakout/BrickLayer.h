#pragma once
#include "Block.h"
#include <vector>

class BrickLayer
{
public:
	BrickLayer() = default;

	void CreateMap(int windowWidth, int windowHeight);

	std::vector<std::vector<Block*>>* GetMap() { return &map; }
	int GetBlockCount();

private:
	std::vector<std::vector<Block*>> map;
};

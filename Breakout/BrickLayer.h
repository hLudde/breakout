#pragma once
#include "Block.h"
#include <vector>

class BrickLayer
{
public:
	BrickLayer() :map(std::vector<Block*>()) {  }

	void CreateMap(int windowWidth, int windowHeight);

	std::vector<Block*>* GetMap() { return &map; }
private:
	std::vector<Block*> map;
};

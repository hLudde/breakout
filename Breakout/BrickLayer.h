#pragma once
#include "Block.h"
#include <vector>
#include <list>

class BrickLayer
{
public:
	void CreateRandomMap(int windowWidth, int windowHeight);
	void CreateMapFromFile(int windowWidth, int WindowHeight, const std::string& filename);

	std::vector<Block*>* GetMap() { return &map; }
	int GetBlockCount();

private:
	void CreateMap(int windowWidth, int windowHeight, int columns, int rows, std::list<int> mapList);


	std::vector<Block*> map;
};

#include "BrickLayer.h"
#include "Block.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

void BrickLayer::CreateMap(const int windowWidth, const int windowHeight, int columns, int rows, std::list<int> mapList)
{
	const int INIT_OFFSET_H = 100;
	const int INIT_OFFSET_W = 1;

	//const int columns = 10;
	//const int bRow = 4;

	const int bWidth = windowWidth/columns;		//Width of the blocks
	const int bHeight = windowHeight/3/rows;	//Height of the blocks

	for(int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			const Vector2 pos{ float(INIT_OFFSET_W + i * bWidth),float(INIT_OFFSET_H + j * bHeight) };
			auto b = new Block{ pos, bHeight - 2, bWidth - 2, mapList.front() };

			mapList.pop_front();
			map.push_back(b);
		}
	}
}

void BrickLayer::CreateRandomMap(int windowWidth, int windowHeight)
{
	std::list<int> mapList{};
	srand(time(nullptr));

	for (int i = 0; i < 40; i++)
	{
		mapList.push_back(rand()%4);
	}

	CreateMap(windowWidth, windowHeight, 10, 4, mapList);
}

void BrickLayer::CreateMapFromFile(int windowWidth, int WindowHeight, const std::string& filename)
{
	std::list<int> mapList{};
	std::vector<char> cList{};

	std::ifstream file;
	file.open(filename);

	while (!file.eof())
	{
		cList.push_back(file.get());
	}
	file.close();

	for (int i = 3; i < cList.size() - 1; i++) //skip first 3 unrelated chars and eof char
	{
		int bType = cList.at(i) - '0';
		mapList.push_back(bType % 4);
	}

	CreateMap(windowWidth, WindowHeight, 10, 4, mapList);
} 

int BrickLayer::GetBlockCount() {
	int count = 0;

	for (auto b : map) {
		if (b->GetHp() > 0)
			count++;
	}

	return count;
}

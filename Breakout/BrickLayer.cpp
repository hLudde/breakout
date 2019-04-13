﻿#include "BrickLayer.h"
#include "Block.h"

void BrickLayer::CreateMap(const int windowWidth, const int windowHeight)
{
	const int INIT_OFFSET_H = 100;
	const int INIT_OFFSET_W = 1;

	const int bCol = 10;
	const int bRow = 4;

	const int bWidth = windowWidth/bCol;		//Width of the blocks
	const int bHeight = windowHeight/3/bRow;	//Height of the blocks

	for (int i = 0; i < bCol; i++) {
		std::vector<Block*> rowVector;
		for (int j = 0; j < bRow; j++)
		{
			Vector2 pos{ float(INIT_OFFSET_W + i * bWidth),float(INIT_OFFSET_H + j * bHeight) };
			auto* b = new Block{ pos,bHeight - 2,bWidth - 2,Uint8(55 + rand() % 200),Uint8(55 + rand() % 200),Uint8(55 + rand() % 200) };
			rowVector.push_back(b);
		}
		map.push_back(rowVector);
	}
}

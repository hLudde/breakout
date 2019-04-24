#include "BrickLayer.h"
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
		for (int j = 0; j < bRow; j++)
		{
			const Vector2 pos{ float(INIT_OFFSET_W + i * bWidth),float(INIT_OFFSET_H + j * bHeight) };
			auto b = new Block{ pos, bHeight - 2, bWidth - 2, rand() % 4 };
			map.push_back(b);
		}
	}
}

int BrickLayer::GetBlockCount() {
	int count = 0;

	for (auto b : map) {
		if (b->GetHp() > 0)
			count++;
	}

	return count;
}

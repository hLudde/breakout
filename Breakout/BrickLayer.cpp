#include "BrickLayer.h"
#include "Block.h"

void BrickLayer::CreateMap(const int windowWidth, const int windowHeight, SDL_Renderer* renderer)
{
	const int INIT_OFFSET_H = 100;
	const int INIT_OFFSET_W = 0;

	const int bWidth = windowWidth/10;		//Width of the blocks
	const int bHeight = windowHeight/3/4;	//Height of the blocks

	for (int i=0;i<10;i++)
		for(int j=0;j<4;j++)
		{
			Vector2 pos{ float(INIT_OFFSET_W + i * bWidth),float(INIT_OFFSET_H + j * bHeight) };
			Block b{ pos,bHeight-2,bWidth-2,Uint8(55 + rand() % 200),Uint8(55 + rand() % 200),Uint8(55 + rand() % 200),renderer };
			map.push_back(b);
		}
}

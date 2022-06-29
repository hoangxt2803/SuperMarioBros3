#include "TileMap.h"
#include "AssetIDs.h"

void CTileMap::Render(float x, float y) {
	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(id)->Draw(x+(float)indexY * TILE_HEIGHT,y+ (float)indexX * TILE_WIDTH);
}



CTileMap::CTileMap(int id, int x, int y)
{
	this->id = id;
	this->indexX = x;
	this->indexY = y;
}

#include "TileMap.h"
#include "AssetIDs.h"

void CTileMap::Render() {
	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(id)->Draw((float)indexY * TILE_HEIGHT, (float)indexX * TILE_WIDTH);
}



CTileMap::CTileMap(int id, int x, int y)
{
	this->id = id;
	this->indexX = x;
	this->indexY = y;
}

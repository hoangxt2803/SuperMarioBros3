#include "TileMap.h"
#include "AssetIDs.h"

void CTileMap::Render() {
	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(id)->Draw(indexY * TILE_HEIGHT, indexX * TILE_WIDTH);
}



CTileMap::CTileMap(int id, float x, float y)
{
	this->id = id;
	this->indexX = x;
	this->indexY = y;
}

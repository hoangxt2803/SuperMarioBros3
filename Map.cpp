#pragma once
#include <iostream>
#include <fstream>
#include "Map.h"

#include "AssetIDs.h"
CMap::CMap() {
	totalRowOfMap = 0;
	totalColOfMap = 0;
	tileSizeX = 0;
	tileSizeY = 0;
	totalRowOfTileSet = 0;
	totalColOfTileSet = 0;
	totalSprites = 0;
	idTextureMap = 0;
	totalTiles = 0;
	texMap = NULL;
	tile = NULL;
	sprites = NULL;
	filePath = NULL;
}
CMap::CMap(LPCWSTR filePath) {
	totalRowOfMap = 0;
	totalColOfMap = 0;
	tileSizeX = 0;
	tileSizeY = 0;
	totalRowOfTileSet = 0;
	totalColOfTileSet = 0;
	totalSprites = 0;
	idTextureMap = 0;
	totalTiles = 0;
	texMap = NULL;
	tile = NULL;
	sprites = NULL;
	this->filePath = filePath;
}
void CMap::LoadMapSprites(int idTextureMap) {
	int left, top, right, bottom;
	texMap = CTextures::GetInstance()->Get(idTextureMap);
	sprites = CSprites::GetInstance();
	for (int index = 0; index < totalTiles; index++) {
		left = index * TILE_HEIGHT;
		top = 0;
		right = left + TILE_WIDTH - 1;
		bottom = TILE_WIDTH - 1;
		sprites->Add(index, left, top, right, bottom, texMap);
	}
}
void CMap::LoadInfoMap(LPCWSTR filePath) {
	ifstream in;

	in.open(filePath);
	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load map content failed ! \n");
		return;
	}
	while (!in.eof())
	{

		// background
		in >> totalColOfMap >> totalRowOfMap >> tileSizeX >> tileSizeY >> totalRowOfTileSet >> totalColOfTileSet >> totalSprites >> idTextureMap >> totalTiles;

		for (int i = 0; i < totalRowOfMap; i++)
		{
			for (int j = 0; j < totalColOfMap; j++)
			{
				int id;
				in >> id;
				CTileMap* tile = new CTileMap(id, i, j);
				tiles.push_back(tile);
			}
		}
		in.close();
	}

}
void CMap::Render() {
	for (int i = 0; i < totalTiles; i++) {
		tiles[i]->Render();
	}
}

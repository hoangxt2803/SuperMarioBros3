#pragma once
#include <iostream>
#include <fstream>
#include "Map.h"

#include "AssetIDs.h"
#include "debug.h"
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
		mapTiles.resize(totalRowOfMap);
		for (int i = 0; i < totalRowOfMap; i++)
		{
			mapTiles[i].resize(totalColOfMap);
			for (int j = 0; j < totalColOfMap; j++)
			{
				in >> mapTiles.at(i).at(j);
				/*int id;
				in >> id;
				CTileMap* tile = new CTileMap(id, i, j);
				tiles.push_back(tile);*/
				
			}
		}
		in.close();
	}

}
void CMap::Render() {
	/*for (int i = 0; i < totalTiles; i++) {
		tiles[i]->Render();
	}*/
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	for (int i = cam_y / TILE_HEIGHT; i < ((cam_y + SCREEN_HEIGHT) / TILE_HEIGHT); i++)
	{
		for (int j = cam_x / TILE_WIDTH; j < ((cam_x + SCREEN_WIDTH) / TILE_WIDTH); j++)
		{
			if (mapTiles[i][j] >= 0)
			{
				float x = j * TILE_WIDTH;
				float y = i * TILE_HEIGHT;
				sprites->Get(mapTiles.at(i).at(j))->Draw(x, y);
			}
		}
	}
}

#include <Windows.h>
#include "TileMap.h"
#include <d3d10.h>
#include <d3dx10.h>
#include"Textures.h"
#include "Sprites.h"

class CMap {
	int totalRowOfMap, totalColOfMap;
	int tileSizeX, tileSizeY;
	int totalRowOfTileSet, totalColOfTileSet;
	int totalSprites;
	int idTextureMap;
	int totalTiles;
	LPCWSTR filePath;
	LPTEXTURE texMap;
	LPTILEMAP tile;
	CSprites* sprites;
	vector<LPTILEMAP> tiles;
public:
	CMap();
	CMap(LPCWSTR filePath);
	void LoadMapSprites(int idTextureMap);
	void LoadInfoMap(LPCWSTR filePath);
	void Render();
	int getIdTextureMap() { return this->idTextureMap; }
	int getTotalRowOfMap() { return this->totalRowOfMap; }
	int getTotalColOfMap() { return this->totalColOfMap; }
};
typedef CMap* LPMAP;
#pragma once
#include "GameObject.h"
class CTileMap {
	int id;
	int indexX;
	int indexY;

public:
	void Render(float x, float y);
	int GetId() { return this->id; }
	CTileMap(int id, int x, int y);
	~CTileMap() {}
};
typedef CTileMap* LPTILEMAP;
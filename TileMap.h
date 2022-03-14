#pragma once
#include "GameObject.h"
class CTileMap {
	int id;
	float indexX;
	float indexY;

public:
	void Render();
	int GetId() { return this->id; }
	CTileMap(int id, float x, float y);
	~CTileMap() {}
};
typedef CTileMap* LPTILEMAP;
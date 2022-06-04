#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TREE_WORLD_MAP 5001


class CTreeWorldMap : public CGameObject {
public:
	CTreeWorldMap(float x, float y);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 1; }
};
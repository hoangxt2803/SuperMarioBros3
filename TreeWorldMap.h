#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TREE_WORLD_MAP 5001
#define ID_ANI_NONE_WORLD_MAP 5005
#define TYPE_TREE	1
#define TYPE_NONE	0

class CTreeWorldMap : public CGameObject {
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	int type;
public:
	CTreeWorldMap(float x, float y, int type);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
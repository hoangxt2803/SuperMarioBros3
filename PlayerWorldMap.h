#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_MARIO_IN_WORLD_MAP		1951
#define PLAYER_BBOX_WIDTH  13
#define PLAYER_BBOX_HEIGHT 12

class CPlayerWorldMap : public CGameObject
{
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
public:
	CPlayerWorldMap(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	//Mario in world map
	void WalkLeft();
	void WalkRight();
	void WalkUp();
	void WalkDown();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};
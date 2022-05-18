#pragma once
#include "GameObject.h"
#include "Mario.h"
#define LEAF_GRAVITY 0.002f
#define LEAF_SPEED_X 0.05f
#define LEAF_SPEED_Y 0.03f
#define LEAF_TIME_CHANGE 500

#define LEAF_WIDTH 16
#define LEAF_HEIGHT 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_STATE_FALL 100
#define LEAF_STATE_INACTIVE 200

#define ID_ANI_LEAF_LEFT 12110	
#define ID_ANI_LEAF_RIGHT 12111	

class CLeaf : public CGameObject
{
	float ax;
	float ay;
	float positionY;
	ULONGLONG change_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void OnCollisionWithMario(LPCOLLISIONEVENT e);
public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};
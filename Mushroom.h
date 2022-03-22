#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_TYPE_GREEN 1
#define MUSHROOM_TYPE_RED 2

#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_INACTIVE 200

#define ID_ANI_MUSHROOM_GREEN 12100
#define ID_ANI_MUSHROOM_RED 12101

class CMushroom : public CGameObject
{
	float ax;
	float ay;
	int type;
	float positionY;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y, int type);
	virtual void SetState(int state);
	int GetType() { return this->type; }
};
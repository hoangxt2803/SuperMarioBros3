#pragma once
#include "GameObject.h"
#define BEFORE_KOOPA_TROOPA_WALKING_SPEED 0.035f
#define BEFORE_KOOPA_TROOPA_GRAVITY 0.002f

#define BEFORE_KOOPA_TROOPA_WIDTH 4
#define BEFORE_KOOPA_TROOPA_BBOX_WIDTH 4
#define BEFORE_KOOPA_TROOPA_BBOX_HEIGHT 24

class CBeforeKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float oldX, oldY;
	BOOLEAN isOnPlatform;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


public:
	CBeforeKoopa(float x, float y);
	void setSpeed(float vX) { this->vx = vX; }
	BOOLEAN getIsOnPlatform() { return this->isOnPlatform; }
	float getY() { return y; }
};
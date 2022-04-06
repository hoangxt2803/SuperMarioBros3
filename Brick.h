#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_BROKEN 10001
#define ID_ANI_QBRICK 10002
#define ID_ANI_QBRICK_EMPTY 10003
#define ID_ANI_QBRICK_UP 10004
#define ID_ANI_QBRICK_COIN 11000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_TYPE_NORMAL 1
#define BRICK_TYPE_BROKEN 2
#define BRICK_TYPE_BROKEN_P 3
#define BRICK_TYPE_QBRICK_1UP 4
#define BRICK_TYPE_QBRICK_COIN 5
#define BRICK_TYPE_QBRICK_MUSHROOM 6

#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_BRICK_UP 200
#define BRICK_STATE_BRICK_EMPTY 300
#define BRICK_STATE_BROKEN_BRICK_COIN 400

#define QBRICK_SPEED_UP 0.1f
#define QBRICK_GRAVITY 0.0015f

class CBrick : public CGameObject {
	int type;
	
	float oldX, oldY;
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	static bool isTranForm;
	CBrick(float x, float y, int type);
	CBrick(float x, float y, int type, int state);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void isBroken();
	virtual void SetState(int state);
	int GetBrickType() { return this->type; }
};
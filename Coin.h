#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define	COIN_HEIGHT 16
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_GRAVITY 0.001f
#define COIN_SPEED_UP 0.4f

#define COIN_TYPE_NORMAL 1
#define COIN_TYPE_QBRICK 2

class CCoin : public CGameObject {
	float ay;
	float oldY;
	int type;
public:
	CCoin(float x, float y);
	CCoin(float x, float y, int type);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	
};
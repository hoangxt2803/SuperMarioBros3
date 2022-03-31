#pragma once
#include "GameObject.h"

#define P_SWITCH_GRAVITY 0.002f
#define P_SWITCH_SPEED 0.05f

#define P_SWITCH_WIDTH 16
#define P_SWITCH_HEIGHT 16
#define P_SWITCH_BBOX_WIDTH 16
#define P_SWITCH_BBOX_HEIGHT 14

#define ID_ANI_P_SWITCH_APPEAR 12500
#define ID_ANI_P_SWITCH_ACTIVATED 12501

#define P_SWITCH_STATE_APPEAR 100
#define P_SWITCH_STATE_ACTIVATED 200
class CPSwitch : public CGameObject
{
	bool isActivated;
	float positionY;
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPSwitch(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};

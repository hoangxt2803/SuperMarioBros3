#pragma once
#include "GameObject.h"

#define PIRANHAPLANT_SPEED 0.015f

#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 24

#define PIRANHAPLANT_TIME	1000


#define PIRANHAPLANT_STATE_IDE	100
#define PIRANHAPLANT_STATE_MOVE	200
#define ID_ANI_PIRANHAPLANT 7001	


class CPiranhaPlant : public CGameObject
{
protected:
	float marioXX, marioYY;
	float oldX, oldY;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPiranhaPlant(float x, float y);
	virtual void SetState(int state);
	void Appear();
};
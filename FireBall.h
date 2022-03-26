#pragma once
#include "GameObject.h"
#define FIRE_VX_SPEED 0.045f
#define FIRE_VY_SPEED 0.035f

#define FIRE_BBOX_WIDTH 9
#define FIRE_BBOX_HEIGHT 9

#define FIRE_STATE_INACTIVE 100
#define FIRE_STATE_ACTIVE 200

#define ID_ANI_FIRE_LEFT 8101
#define ID_ANI_FIRE_RIGHT 8102
class CFireBall : public CGameObject
{
	float oldX, oldY;
	
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


public:
	CFireBall(float x, float y, int nx, int ny);
	//virtual void SetState(int state);
	//void SetGravity(int nX, int nY) { this->nx = nX; this->ny = nY; }
};
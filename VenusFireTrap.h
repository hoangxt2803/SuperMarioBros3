#pragma once
#include "GameObject.h"
#include "FireBall.h"

#define VENUS_FIRE_TRAP_SPEED 0.015f

#define VENUS_FIRE_TRAP_TYPE_RED 1
#define VENUS_FIRE_TRAP_TYPE_GREEN 2

#define VENUS_FIRE_TRAP_RED_BBOX_WIDTH 16
#define VENUS_FIRE_TRAP_RED_BBOX_HEIGHT 32

#define VENUS_FIRE_TRAP_GREEN_BBOX_WIDTH 16
#define VENUS_FIRE_TRAP_GREEN_BBOX_HEIGHT 24

#define VENUS_FIRE_TRAP_FIRE_TIME	2000


#define VENUS_FIRE_TRAP_STATE_IDE	100
#define VENUS_FIRE_TRAP_STATE_MOVE	200
#define VENUS_FIRE_TRAP_STATE_SHOOT	300

#define ID_ANI_VENUS_FIRE_TRAP_RED_LEFT_DOWN 7101	
#define ID_ANI_VENUS_FIRE_TRAP_RED_LEFT_UP 7102
#define ID_ANI_VENUS_FIRE_TRAP_RED_RIGHT_DOWN 7103
#define ID_ANI_VENUS_FIRE_TRAP_RED_RIGHT_UP 7104

#define ID_ANI_VENUS_FIRE_TRAP_GREEN_LEFT_DOWN 7105
#define ID_ANI_VENUS_FIRE_TRAP_GREEN_LEFT_UP 7106
#define ID_ANI_VENUS_FIRE_TRAP_GREEN_RIGHT_DOWN 7107
#define ID_ANI_VENUS_FIRE_TRAP_GREEN_RIGHT_UP 7108

class CVenusFireTrap : public CGameObject
{
protected:
	
	float oldX, oldY;
	int type;
	float marioXX, marioYY;
	ULONGLONG fire_start;
	int countFire = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CVenusFireTrap(float x, float y, int type);
	virtual void SetState(int state);
	void ShootFireball();
	void Appear();
};
#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_PREPARE_FLY_SPEED 0.15f
#define GOOMBA_FLY_SPEED 0.4f

#define GOOMBA_TYPE_NORMAL 1
#define GOOMBA_TYPE_RED 2

#define GOOMBA_LEVEL_NORMAL 1
#define GOOMBA_LEVEL_WING 2

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7
#define GOOMBA_PREPARE_FLY_BBOX_WIDTH 20
#define GOOMBA_PREPARE_FLY_BBOX_HEIGHT 22
#define GOOMBA_FLY_BBOX_WIDTH 20
#define GOOMBA_FLY_BBOX_HEIGHT 22

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_WALKING_TIME	1000
#define GOOMBA_FLY_TIME	300

#define GOOMBA_FLY 1

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_PREPARE_FLY 300
#define GOOMBA_STATE_FLY_WALKING 400
#define GOOMBA_STATE_FLY_JUMPING 500
#define GOOMBA_STATE_DEATH 600

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_FLY_WALKING 5002
#define ID_ANI_GOOMBA_FLY 5003
#define ID_ANI_GOOMBA_DEATH 5008

#define ID_ANI_PARAGOOMBA_FLY_WALKING 5004
#define ID_ANI_PARAGOOMBA_FLY 5005
#define ID_ANI_PARAGOOMBA_WALKING 5006
#define ID_ANI_PARAGOOMBA_DIE 5007
#define ID_ANI_PARAGOOMBA_DEATH 5009

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	
	int type;
	int level;
	int countFly = 0;
	//map 1-1, kiểm tra khi mario đến vị trí (x,y) -> goomba, wing goomba xuất hiện
	bool isActive;

	BOOLEAN isOnPlatform;
	ULONGLONG die_start;
	ULONGLONG walking_start;
	ULONGLONG prepare_fly_start;

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWitHiddenObject(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type, int level, bool isActive);
	void SetState(int state);
	void SetLevel(int l);
	int GetLevel() { return this->level; }
	void Appear(bool isActive);
};
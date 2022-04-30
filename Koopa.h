#pragma once
#include "GameObject.h"
#include "BeforeKoopa.h"
#define KOOPA_TROOPA_GRAVITY 0.002f
#define KOOPA_TROOPA_WALKING_SPEED 0.035f
#define KOOPATROOPA_SHELL_SPEED 0.145f
#define KOOPATROOPA_SHELL_SPEED_DROP 0.25f
#define KOOPATROOPA_FLY_SPEED 0.45f
#define KOOPATROOPA_TIME_RELEASE_KOOPA 10000

#define KOOPA_TROOPA_WIDTH 16
#define KOOPA_TROOPA_BBOX_WIDTH 16
#define KOOPA_TROOPA_BBOX_HEIGHT 24
#define KOOPA_TROOPA_BBOX_HEIGHT_SHELL 14
#define KOOPA_TROOPA_BBOX_WIDTH_SHELL 16
#define KOOPA_TROOPA_BBOX_HEIGHT_DIE 14

#define KOOPA_TROOPA_TYPE_RED 1
#define KOOPA_TROOPA_TYPE_GREEN 2

#define	KOOPA_TROOPA_LEVEL_NORMAL	1
#define	KOOPA_TROOPA_LEVEL_WING		2

#define KOOPA_TROOPA_STATE_WALKING 100
#define KOOPA_TROOPA_STATE_SHELL 200
#define KOOPA_TROOPA_STATE_SHELL_MOVE 300
#define KOOPA_PARATROOPA_STATE_FLY 400
#define KOOPA_TROOPA_STATE_WALKING_LEFT 500
#define KOOPA_TROOPA_STATE_WALKING_RIGHT 600
#define KOOPA_TROOPA_STATE_HOLED 700

#define ID_ANI_RED_KOOPA_TROOPA_WALKING_LEFT 5100
#define ID_ANI_RED_KOOPA_TROOPA_WALKING_RIGHT 5101
#define ID_ANI_RED_KOOPA_TROOPA_SHELL 5102
#define ID_ANI_RED_KOOPA_TROOPA_SHELL_MOVE 5103
#define ID_ANI_RED_KOOPA_PARATROOPA_FLY_LEFT 5104
#define ID_ANI_RED_KOOPA_PARATROOPA_FLY_RIGHT 5105

#define ID_ANI_GREEN_KOOPA_TROOPA_WALKING_LEFT 5110
#define ID_ANI_GREEN_KOOPA_TROOPA_WALKING_RIGHT 5111
#define ID_ANI_GREEN_KOOPA_TROOPA_SHELL 5112
#define ID_ANI_GREEN_KOOPA_TROOPA_SHELL_MOVE 5113
#define ID_ANI_GREEN_KOOPA_PARATROOPA_FLY_LEFT 5114
#define ID_ANI_GREEN_KOOPA_PARATROOPA_FLY_RIGHT 5115

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;
	int level;
	bool isHolded;
	bool isDroped;
	bool isKoopaToShell;
	bool isShellToKoopa;
	ULONGLONG release_start;
	BOOLEAN isOnPlatform;
	ULONGLONG fly_start;
	CBeforeKoopa* beforeKoopa = NULL;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrokenBrick(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y, int type, int level);
	void IsKicked(int nx);
	void IsDroped(int nx);
	void IsHolded();
	void SetState(int state);
	void SetKoopaToShell(boolean KoopaToShell);
	void SetLevel(int l);
	int GetLevel() { return this->level; }
	void SetIsHolded(bool value) { isHolded = value; };
	void SetIsDroped(bool value) { isDroped = value; };
	bool GetIsShellToKoopa() { return isKoopaToShell; }
};
#pragma once
#include"GameObject.h"
//  TAIL
#define TAIL_BBOX_WIDTH					5
#define TAIL_BBOX_HEIGHT				5

#define TAIL_STATE_ATTACK				0
#define TAIL_STATE_INACTIVE				1
class CTail :public CGameObject
{
	float oldX = 0;
	void GetBoundingBox(float& left, float& top,
		float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y) : CGameObject(x, y) {
		this->SetState(TAIL_STATE_INACTIVE);
	}
	void SetState(int state);
	void Attack(float x, float y, int nx) {
		this->x = x;
		this->y = y;
		this->oldX = x;
		this->nx = nx;
		//this->isEnable = true;
		
		this->SetState(TAIL_STATE_ATTACK);
	};
	int GetWidth() { return TAIL_BBOX_WIDTH; };
};


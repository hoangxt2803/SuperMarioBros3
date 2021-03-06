#include "Coin.h"

CCoin::CCoin(float x, float y) :CGameObject(x, y) {
	this->vx = 0;
	this->vy = 0;
	this->ay = 0;
	this->oldY = y;
	this->type = COIN_TYPE_NORMAL;
}
CCoin::CCoin(float x, float y, int type) :CGameObject(x, y) {
	this->vx = 0;
	this->vy = -COIN_SPEED_UP;
	this->ay = COIN_GRAVITY;
	this->oldY = y;
	this->type = type;
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->type == COIN_TYPE_QBRICK) {
		x += vx * dt;
		y += vy * dt;
		vy += ay * dt;
		if (y + COIN_HEIGHT / 2 >= oldY && vy > 0) {
			this->Delete();
		}
	}
	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

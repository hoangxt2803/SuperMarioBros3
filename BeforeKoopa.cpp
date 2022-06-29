#include "BeforeKoopa.h"
#include "Mario.h"
CBeforeKoopa::CBeforeKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BEFORE_KOOPA_TROOPA_GRAVITY;
	oldX = x;
	oldY = y;
}

void CBeforeKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BEFORE_KOOPA_TROOPA_BBOX_WIDTH / 2;
	top = y - BEFORE_KOOPA_TROOPA_BBOX_HEIGHT / 2;
	right = left + BEFORE_KOOPA_TROOPA_BBOX_WIDTH;
	bottom = top + BEFORE_KOOPA_TROOPA_BBOX_HEIGHT;
}

void CBeforeKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CBeforeKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{


	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)
			isOnPlatform = true;

	}
}


void CBeforeKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	bool _isTransFormMario = CMario::isTranFormMario;
	if (_isTransFormMario == true)
		return;
	vy += ay * dt;
	vx += ax * dt;
	if (y > oldY) {
		isOnPlatform = false;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBeforeKoopa::Render()
{
	//RenderBoundingBox();
}
#include "PSwitch.h"
CPSwitch::CPSwitch(float x, float y) :CGameObject(x, y)
{
	this->isActivated = false;
	state = P_SWITCH_STATE_APPEAR;
	vy = -P_SWITCH_SPEED;
	this->positionY = y - P_SWITCH_WIDTH;
}

void CPSwitch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - P_SWITCH_BBOX_WIDTH / 2;
	top = y - P_SWITCH_BBOX_HEIGHT / 2;
	right = left + P_SWITCH_BBOX_WIDTH;
	bottom = top + P_SWITCH_BBOX_HEIGHT;
}



void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (GetState() == P_SWITCH_STATE_APPEAR) {

		if (this->y <= positionY) {
			vy = 0;
			this->y = positionY;
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CPSwitch::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CPSwitch::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CPSwitch::Render()
{
	int aniId = -1;
	if (state == P_SWITCH_STATE_APPEAR)
		aniId = ID_ANI_P_SWITCH_APPEAR;
	else if (state == P_SWITCH_STATE_ACTIVATED)
		aniId = ID_ANI_P_SWITCH_ACTIVATED;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPSwitch::SetState(int state)
{
	switch (state)
	{
	case P_SWITCH_STATE_APPEAR:
		vx = 0;
		vy = -P_SWITCH_SPEED;
		break;
	case P_SWITCH_STATE_ACTIVATED:
		break;
	}
	CGameObject::SetState(state);
}


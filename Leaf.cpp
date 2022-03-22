#include "Leaf.h"
CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	state = LEAF_STATE_INACTIVE;
	vy = -0.1f;
	//SetState(MUSHROOM_STATE_INACTIVE);
	this->positionY = y - LEAF_HEIGHT * 3;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}



void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (GetState() == LEAF_STATE_INACTIVE)
	{
		if (this->y <= positionY) {
			this->y = positionY;
			state = LEAF_STATE_FALL;
		}
	}
	if (state == LEAF_STATE_FALL) {
		if (vy <= 0)
			vy += LEAF_GRAVITY * dt;
		if (vy > 0 && vx == 0)
		{
			vy = LEAF_SPEED_Y;
			vx = LEAF_SPEED_X;
			change_start = GetTickCount();
		}
		else
		{
			if ((DWORD)GetTickCount() - change_start > LEAF_TIME_CHANGE)
			{
				vx = -vx;
				this->nx = -this->nx;
				change_start = GetTickCount();
			}

		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	else return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CLeaf::Render()
{
	int aniId = -1;
	aniId = ID_ANI_LEAF_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CLeaf::SetState(int state)
{

	switch (state)
	{
	case LEAF_STATE_FALL:
		vx = LEAF_SPEED_X;
		ay = LEAF_GRAVITY;
		vy = LEAF_SPEED_Y;
		change_start = GetTickCount();
		break;
	case LEAF_STATE_INACTIVE:
		vx = 0;
		vy = 0;

		break;
	}
	CGameObject::SetState(state);
}


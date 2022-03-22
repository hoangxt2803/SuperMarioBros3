#include "Mushroom.h"
CMushroom::CMushroom(float x, float y, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->type = type;
	state = MUSHROOM_STATE_INACTIVE;
	vy = -MUSHROOM_WALKING_SPEED;
	//SetState(MUSHROOM_STATE_INACTIVE);
	this->positionY = y - MUSHROOM_HEIGHT;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}



void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (GetState() == MUSHROOM_STATE_INACTIVE) {

		if (this->y <= positionY) {
			this->y = positionY;
			SetState(MUSHROOM_STATE_WALKING);
		}

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CMushroom::Render()
{
	int aniId = -1;
	if (this->type == MUSHROOM_TYPE_GREEN) {
		aniId = ID_ANI_MUSHROOM_GREEN;
	}
	else if (this->type == MUSHROOM_TYPE_RED) {
		aniId = ID_ANI_MUSHROOM_RED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{

	switch (state)
	{
	case MUSHROOM_STATE_INACTIVE:
		vx = 0;
		vy = -MUSHROOM_WALKING_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = MUSHROOM_WALKING_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
	CGameObject::SetState(state);
}


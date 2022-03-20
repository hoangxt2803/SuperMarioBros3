#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type, int level) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	this->level = level;
	this->type = type;
	SetLevel(level);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else if (state == GOOMBA_STATE_PREPARE_FLY || state == GOOMBA_STATE_FLY_WALKING)
	{
		left = x - GOOMBA_PREPARE_FLY_BBOX_WIDTH / 2;
		top = y - GOOMBA_FLY_BBOX_HEIGHT / 2;
		right = left + GOOMBA_PREPARE_FLY_BBOX_WIDTH;
		bottom = top + GOOMBA_FLY_BBOX_HEIGHT;
	}
	else if (state == GOOMBA_STATE_FLY_JUMPING)
	{
		left = x - GOOMBA_FLY_BBOX_WIDTH / 2;
		top = y - GOOMBA_FLY_BBOX_HEIGHT / 2;
		right = left + GOOMBA_FLY_BBOX_WIDTH;
		bottom = top + GOOMBA_FLY_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (isOnPlatform && (state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (isOnPlatform && (state == GOOMBA_STATE_FLY_WALKING) && (GetTickCount64() - walking_start > GOOMBA_WALKING_TIME) && level != GOOMBA_LEVEL_NORMAL) {
		SetState(GOOMBA_STATE_PREPARE_FLY);
	}
	else if (isOnPlatform && countFly < GOOMBA_FLY && (state == GOOMBA_STATE_PREPARE_FLY) && level != GOOMBA_LEVEL_NORMAL && GetTickCount64() - prepare_fly_start > GOOMBA_FLY_TIME) {
		countFly++;
		SetState(GOOMBA_STATE_PREPARE_FLY);

	}
	else if (isOnPlatform && countFly == GOOMBA_FLY && (state == GOOMBA_STATE_PREPARE_FLY) && level != GOOMBA_LEVEL_NORMAL && GetTickCount64() - prepare_fly_start > GOOMBA_FLY_TIME) {

		SetState(GOOMBA_STATE_FLY_JUMPING);

	}
	else if (isOnPlatform && countFly == GOOMBA_FLY && (state == GOOMBA_STATE_FLY_JUMPING) && level != GOOMBA_LEVEL_NORMAL) {

		SetState(GOOMBA_STATE_FLY_WALKING);
		countFly = 0;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;
	if (this->type == GOOMBA_TYPE_NORMAL) {
		if (state == GOOMBA_STATE_WALKING)
		{
			aniId = ID_ANI_GOOMBA_WALKING;
		}
		else if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_ANI_GOOMBA_DIE;
		}
		else if (state == GOOMBA_STATE_DEATH)
		{
			aniId = ID_ANI_GOOMBA_DEATH;
		}
		else if (state == GOOMBA_STATE_PREPARE_FLY || state == GOOMBA_STATE_FLY_JUMPING)
		{
			aniId = ID_ANI_GOOMBA_FLY;
		}
		else if (state == GOOMBA_STATE_FLY_WALKING)
		{
			aniId = ID_ANI_GOOMBA_FLY_WALKING;
		}

	}
	else if (this->type == GOOMBA_TYPE_RED) {
		if (state == GOOMBA_STATE_WALKING)
		{
			aniId = ID_ANI_PARAGOOMBA_WALKING;
		}
		else if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_ANI_PARAGOOMBA_DIE;
		}
		else if (state == GOOMBA_STATE_PREPARE_FLY || state == GOOMBA_STATE_FLY_JUMPING)
		{
			aniId = ID_ANI_PARAGOOMBA_FLY;
		}
		else if (state == GOOMBA_STATE_FLY_WALKING)
		{
			aniId = ID_ANI_PARAGOOMBA_FLY_WALKING;
		}
		else if (state == GOOMBA_STATE_DEATH)
		{
			aniId = ID_ANI_PARAGOOMBA_DEATH;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		isOnPlatform = true;
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_PREPARE_FLY:
		prepare_fly_start = (DWORD)GetTickCount64();
		isOnPlatform = false;
		vy = -GOOMBA_PREPARE_FLY_SPEED;
		break;
	case GOOMBA_STATE_FLY_JUMPING:
		isOnPlatform = false;
		vy = -GOOMBA_FLY_SPEED;
		break;
	case GOOMBA_STATE_FLY_WALKING:
		isOnPlatform = true;
		walking_start = (DWORD)GetTickCount64();
		break;
	case GOOMBA_STATE_DEATH:
		isOnPlatform = false;
		vx = 0;
		vy = -GOOMBA_FLY_SPEED;
		ax = 0;
		break;
	}
}
void CGoomba::SetLevel(int l)
{
	level = l;
	if (level > GOOMBA_LEVEL_NORMAL)
	{
		vx = GOOMBA_WALKING_SPEED;
		countFly = 0;
		SetState(GOOMBA_STATE_FLY_WALKING);
	}
	else
		SetState(GOOMBA_STATE_WALKING);
}

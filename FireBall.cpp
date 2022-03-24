#include "FireBall.h"
CFireBall::CFireBall(float x, float y) :CGameObject(x, y)
{
	state = FIRE_STATE_INACTIVE;
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BBOX_WIDTH / 2;
	top = y - FIRE_BBOX_HEIGHT / 2;
	right = left + FIRE_BBOX_WIDTH;
	bottom = top + FIRE_BBOX_HEIGHT;
}


void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(state == FIRE_STATE_INACTIVE)
		return;
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFireBall::Render()
{
	int aniId = -1;
	if (state == FIRE_STATE_INACTIVE)
		return;
	else if (state == FIRE_STATE_ACTIVE) {
		if (vx < 0) {
			aniId = ID_ANI_FIRE_LEFT;
		}
		else if (vx > 0)
			aniId = ID_ANI_FIRE_RIGHT;
	}
	if (aniId == -1) {
		aniId = ID_ANI_FIRE_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_STATE_INACTIVE:
		vx = 0;
		vy = 0;
		break;
	case FIRE_STATE_ACTIVE:
		vx = FIRE_VX_SPEED * nx;
		vy = FIRE_VY_SPEED * ny;
		break;

	}
}
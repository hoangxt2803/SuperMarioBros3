#include "PlayerWorldMap.h"
#include "TreeWorldMap.h"

CPlayerWorldMap::CPlayerWorldMap(float x, float y) :CGameObject(x, y)
{
}

void CPlayerWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlayerWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_MARIO_IN_WORLD_MAP;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPlayerWorldMap::WalkLeft()
{
	this->x -= 16;
	this->nx = -1;
	//DebugOut(L"nx: %d \n", this->nx);
}

void CPlayerWorldMap::WalkRight()
{
	this->x += 16;
	this->nx = 1;
	//DebugOut(L"nx: %d \n", this->nx);
}

void CPlayerWorldMap::WalkUp()
{
	this->y -= 16;
	this->ny = -1;
	//DebugOut(L"ny: %d \n", this->ny);
}

void CPlayerWorldMap::WalkDown()
{
	this->y += 16;
	this->ny = 1;
	//DebugOut(L"ny: %d \n", this->ny);
}

void CPlayerWorldMap::OnNoCollision(DWORD dt)
{
}

void CPlayerWorldMap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTreeWorldMap*>(e->obj))
	{
		DebugOut(L"ny: %d \n", this->ny);
		if (this->ny > 0)
			DebugOut(L"ny1: %d \n", this->ny);
		else if (this->ny < 0)
			DebugOut(L"ny2: %d \n", this->ny);
		else if (this->nx > 0)
			DebugOut(L"nx1: %d \n", this->nx);
		else if (this->nx < 0)
			DebugOut(L"nx2: %d \n", this->nx);
	}
}

void CPlayerWorldMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLAYER_BBOX_WIDTH / 2;
	top = y - PLAYER_BBOX_HEIGHT / 2;
	right = left + PLAYER_BBOX_WIDTH;
	bottom = top + PLAYER_BBOX_HEIGHT;
}

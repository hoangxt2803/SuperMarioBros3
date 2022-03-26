#include "PiranhaPlant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "AssetIDs.h"
CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->oldX = x;
	this->oldY = y;
	this->SetState(PIRANHAPLANT_STATE_MOVE);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CPiranhaPlant::Appear() {
	if (marioXX < x)
	{
		if ((marioXX + SCREEN_WIDTH / 2) > x)
			state = PIRANHAPLANT_STATE_MOVE;
		else
		{
			state = PIRANHAPLANT_STATE_IDE;
			SetPosition(oldX, oldY);
		}
	}
	else if (marioXX > x) {
		if ((marioXX - SCREEN_WIDTH / 2) < x)
			state = PIRANHAPLANT_STATE_MOVE;
		else
		{
			state = PIRANHAPLANT_STATE_IDE;
			SetPosition(oldX, oldY);
		}
	}
}
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)playscreen->GetPlayer();

	mario->GetPosition(marioXX, marioYY);
	//appear
	Appear();
	if (this->y <= oldY - PIRANHAPLANT_BBOX_HEIGHT || this->y >= oldY) {
		vy = -vy;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PIRANHAPLANT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_IDE:
		vx = 0;
		vy = 0;
		break;
	case PIRANHAPLANT_STATE_MOVE:
		vy = -PIRANHAPLANT_SPEED;
		break;
	}
}

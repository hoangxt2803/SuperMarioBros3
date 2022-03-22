#include "Brick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"

CBrick::CBrick(float x, float y, int type) :CGameObject(x, y) {
	this->type = type;
	this->oldX = x;
	this->oldY = y;
	this->SetState(BRICK_STATE_NORMAL);
	vx = 0;
	vy = 0;
}


void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	if (state == BRICK_STATE_QBRICK_UP) {
		if (y <= oldY - BRICK_BBOX_HEIGHT / 2) {
			CGameObject* obj = NULL;

			if (this->type == BRICK_TYPE_QBRICK_COIN)
			{
				obj = new CCoin(oldX, oldY, COIN_TYPE_QBRICK);
			}
			else if (this->type == BRICK_TYPE_QBRICK_MUSHROOM) {
				if (mario->GetLevel() == MARIO_LEVEL_SMALL)
					obj = new CMushroom(oldX, oldY, MUSHROOM_TYPE_RED);
				else if (mario->GetLevel() > MARIO_LEVEL_SMALL)
					obj = new CLeaf(oldX, oldY);
			}
			else if (this->type == BRICK_TYPE_QBRICK_1UP) {
				obj = new CMushroom(oldX, oldY, MUSHROOM_TYPE_GREEN);
				// +1up 
				
			}
			LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			playscreen->AddObject(obj);
			SetState(BRICK_STATE_QBRICK_EMPTY);
			SetPosition(oldX, oldY);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == BRICK_STATE_NORMAL)
	{
		if (this->type == BRICK_TYPE_NORMAL)
		{
			aniId = ID_ANI_BRICK;
		}
		else if (this->type == BRICK_TYPE_BROKEN || this->type == BRICK_TYPE_BROKEN_P) {
			aniId = ID_ANI_BRICK_BROKEN;
		}
		else if (this->type == BRICK_TYPE_QBRICK_1UP || this->type == BRICK_TYPE_QBRICK_MUSHROOM || this->type == BRICK_TYPE_QBRICK_COIN) {
			aniId = ID_ANI_QBRICK;
		}
	}
	else if (state == BRICK_STATE_QBRICK_UP)
	{
		aniId = ID_ANI_QBRICK_UP;
	}
	else if (state == BRICK_STATE_QBRICK_EMPTY)
	{
		aniId = ID_ANI_QBRICK_EMPTY;
	}
	
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}


void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_NORMAL:
		vy = 0;
		break;
	case BRICK_STATE_QBRICK_UP:
		//ay = -QBRICK_GRAVITY;
		vy = -QBRICK_SPEED_UP;
		break;
	case BRICK_STATE_QBRICK_EMPTY:
		vy = 0;
		break;
	}
}
void CBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
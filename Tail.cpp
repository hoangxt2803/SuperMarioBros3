#include "Tail.h"
#include "Brick.h"
#include "HUD.h"
#include "Game.h"
#include "PlayScene.h"
#include "Koopa.h"
#include "BrickEffect.h"
void CTail::Render()
{
	if (state == TAIL_STATE_INACTIVE)
		return;
	RenderBoundingBox();
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	
	
}
void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (e->nx != 0) {
		goomba->SetState(GOOMBA_STATE_DEATH);
	}
	
}

void CTail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->nx != 0) {
		koopa->SetState(KOOPA_TROOPA_STATE_DEATH);
	}
	
}

void CTail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->nx != 0)
	{
		if (brick->GetBrickType() == BRICK_TYPE_BROKEN_P)
			brick->SetState(BRICK_STATE_BRICK_UP);
		if (brick->GetBrickType() == BRICK_TYPE_BROKEN) {
			CGameObject* obj = NULL;
			float XX, YY;
			brick->GetPosition(XX, YY);
			obj = new CBrickEffect(XX, YY);
			LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			playscreen->AddObject(obj);
			brick->Delete();
		}
		if (brick->GetBrickType() == BRICK_TYPE_QBRICK_1UP || brick->GetBrickType() == BRICK_TYPE_QBRICK_MUSHROOM || brick->GetBrickType() == BRICK_TYPE_QBRICK_COIN) {
			if (brick->GetState() != BRICK_STATE_BRICK_EMPTY)
			{
				brick->SetState(BRICK_STATE_BRICK_UP);
			}
		}
		if (brick->GetBrickType() == BRICK_TYPE_QBRICK_COIN && brick->GetState() != BRICK_STATE_BRICK_EMPTY) {
			CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
			hub->CoinPlus();
			brick->SetState(BRICK_STATE_BRICK_UP);
		}
	}
	
}

void CTail::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case TAIL_STATE_ATTACK:
		vx = 0.2f * nx;
		vy = 0;
		break;
	case TAIL_STATE_INACTIVE:
		vx = 0;
		break;
	}
}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == TAIL_STATE_INACTIVE)
		return;
	if (((x >= oldX + 6) && nx > 0) || ((x <= oldX - 6) && nx < 0)) {
		this->SetState(TAIL_STATE_INACTIVE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::GetBoundingBox(float& left, float& top,
	float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

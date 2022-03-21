#include "Koopa.h"
#include "Goomba.h"
#include "Pipe.h"
#include "Mario.h"
#include "SPlatform.h"
#include "PlayScene.h"
#include "Brick.h"
CKoopa::CKoopa(float x, float y, int type, int level) :CGameObject(x, y)
{
	this->level = level;
	this->type = type;
	this->ax = 0;
	this->ay = KOOPA_TROOPA_GRAVITY;
	isKoopaToShell = false;
	isShellToKoopa = false;
	SetLevel(level);
	isOnPlatform = true;
	this->fly_start = 0;
	isHolded = false;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	playscreen->AddObject(beforeKoopa);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == KOOPA_TROOPA_STATE_SHELL || state == KOOPA_TROOPA_STATE_SHELL_MOVE)
	{
		left = x - KOOPA_TROOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_TROOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_TROOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPA_TROOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_TROOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_TROOPA_BBOX_WIDTH;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) {
		OnCollisionWithGoomba(e);
	}
	
	if (e->obj->IsBlocking()) {
		if (e->ny != 0)
		{
			vy = 0;
			if (e->ny < 0)
				isOnPlatform = true;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}


}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (this->state == KOOPA_TROOPA_STATE_SHELL_MOVE || this->state == KOOPA_TROOPA_STATE_SHELL) {
		if (goomba->GetState() == GOOMBA_STATE_WALKING)
		{
			goomba->SetState(GOOMBA_STATE_DEATH);
		}
		else if (goomba->GetLevel() != GOOMBA_LEVEL_NORMAL)
		{
			goomba->SetLevel(GOOMBA_LEVEL_NORMAL);
		}
	}


}


void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//shell to koopa
	
	if (isKoopaToShell)
		beforeKoopa->SetSpeed(0, 0);
	if (state == KOOPA_TROOPA_STATE_WALKING) {
		beforeKoopa->setSpeed(vx);
		if (!beforeKoopa->getIsOnPlatform()) {
			vx = -vx;
			if (vx > 0) {
				beforeKoopa->SetPosition(x + KOOPA_TROOPA_WIDTH / 2, y);
			}
			else if (vx < 0) {
				beforeKoopa->SetPosition(x - KOOPA_TROOPA_WIDTH / 2, y);
			}

		}
	}
	if (isOnPlatform && state == KOOPA_PARATROOPA_STATE_FLY && GetTickCount64() - fly_start > 1000) {
		fly_start = (DWORD)GetTickCount64();
		vy = -KOOPATROOPA_FLY_SPEED;
		ay = KOOPA_TROOPA_GRAVITY;
		isOnPlatform = false;
	}
	//mario hold koopa
	
	//Mario drop koopa
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = -1;
	if (this->type == KOOPA_TROOPA_TYPE_RED) {
		if (vx > 0 && state == KOOPA_TROOPA_STATE_WALKING)
		{
			aniId = ID_ANI_RED_KOOPA_TROOPA_WALKING_RIGHT;
		}
		else if (vx < 0 && state == KOOPA_TROOPA_STATE_WALKING) {
				aniId = ID_ANI_RED_KOOPA_TROOPA_WALKING_LEFT;
			}
		else if (state == KOOPA_TROOPA_STATE_SHELL || state == KOOPA_TROOPA_STATE_HOLED)
			{
				aniId = ID_ANI_RED_KOOPA_TROOPA_SHELL;
			}
		else if (state == KOOPA_TROOPA_STATE_SHELL_MOVE)
			{
				aniId = ID_ANI_RED_KOOPA_TROOPA_SHELL_MOVE;
			}
		else if (vx < 0 && state == KOOPA_PARATROOPA_STATE_FLY)
		{
			aniId = ID_ANI_RED_KOOPA_PARATROOPA_FLY_LEFT;
		}
		else if (vx > 0 && state == KOOPA_PARATROOPA_STATE_FLY)
		{
			aniId = ID_ANI_RED_KOOPA_PARATROOPA_FLY_RIGHT;
		}
	}
	else if ((this->type == KOOPA_TROOPA_TYPE_GREEN)) {
		if (vx > 0 && state == KOOPA_TROOPA_STATE_WALKING)
		{
			aniId = ID_ANI_GREEN_KOOPA_TROOPA_WALKING_RIGHT;
		}
		else if (vx < 0 && state == KOOPA_TROOPA_STATE_WALKING) {
			aniId = ID_ANI_GREEN_KOOPA_TROOPA_WALKING_LEFT;
		}
		else if (vx < 0 && state == KOOPA_PARATROOPA_STATE_FLY)
		{
			aniId = ID_ANI_GREEN_KOOPA_PARATROOPA_FLY_LEFT;
		}
		else if (vx > 0 && state == KOOPA_PARATROOPA_STATE_FLY)
		{
			aniId = ID_ANI_GREEN_KOOPA_PARATROOPA_FLY_RIGHT;
		}
		else if (state == KOOPA_TROOPA_STATE_SHELL || state == KOOPA_TROOPA_STATE_HOLED)
		{
			aniId = ID_ANI_GREEN_KOOPA_TROOPA_SHELL;
		}
		else if (state == KOOPA_TROOPA_STATE_SHELL_MOVE)
		{
			aniId = ID_ANI_GREEN_KOOPA_TROOPA_SHELL_MOVE;
		}

	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CKoopa::IsKicked(int n)
{
	this->nx = n;
	vx = nx * KOOPATROOPA_SHELL_SPEED;
}
void CKoopa::IsDroped(int n)
{
	this->isHolded = false;
	this->isDroped = false;
	this->nx = n;
	SetState(KOOPA_TROOPA_STATE_SHELL_MOVE);
	vx = nx * KOOPATROOPA_SHELL_SPEED_DROP;
	vy = KOOPA_TROOPA_WALKING_SPEED;
}

void CKoopa::SetKoopaToShell(boolean isKoopaToShell)
{
	this->isKoopaToShell = isKoopaToShell;
}
void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_TROOPA_STATE_SHELL:
		release_start = GetTickCount64();
		if (isKoopaToShell == true)
			y += (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_TROOPA_STATE_WALKING:
		if (beforeKoopa == NULL) {
			beforeKoopa = new CBeforeKoopa(x - BEFORE_KOOPA_TROOPA_WIDTH, y);
		}
		isHolded = false;
		if (isShellToKoopa == true)
		{
			y -= (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_SHELL) / 2;
			isShellToKoopa = false;
		}
		vx = -KOOPA_TROOPA_WALKING_SPEED;
		ay = KOOPA_TROOPA_GRAVITY;
		break;
	case KOOPA_TROOPA_STATE_SHELL_MOVE:
		isHolded = false;
		vx = -KOOPATROOPA_SHELL_SPEED;
		ay = KOOPA_TROOPA_GRAVITY;
		break;
	case KOOPA_PARATROOPA_STATE_FLY:

		vx = KOOPA_TROOPA_WALKING_SPEED;
		ay = KOOPA_TROOPA_GRAVITY;
		break;
	case KOOPA_TROOPA_STATE_HOLED:
		vx = 0;
		ay = 0;
		break;
	}

}


void CKoopa::SetLevel(int l)
{
	level = l;
	if (level > KOOPA_TROOPA_LEVEL_NORMAL)
		SetState(KOOPA_PARATROOPA_STATE_FLY);
	else
		SetState(KOOPA_TROOPA_STATE_WALKING);
}
